#include "header.h"

int is_nid_unique(blockchain_t* blockchain, int nid)
{
    Node* node_temp = blockchain->head;
    
    while (node_temp != NULL) 
    {
        if ( node_temp->nid == nid)
        {
           return 0;
        }
       //the whole list of bids needs to be shifted
       node_temp = node_temp->next;
    }
    return 1;
}

// build nodes and attach to linked list
Node* create_node(blockchain_t* blockchain, int nid) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        _printf("nok: error creating new node\n");
        return 0;
    }
    blockchain->node_count++;
    new_node->nid = nid;    
    //new_node->sync = sync;
    new_node->bids_in_use = 0;
    // if blockchain is empty
    if (blockchain->head == NULL) {
        blockchain->head = new_node;
        blockchain->tail = new_node;
        //blockchain->sync = new_node;
    } else {
        blockchain->tail->next = new_node;
        blockchain->tail = new_node;
    }
    new_node->next = NULL;
    new_node->block = NULL;
    new_node->block_tail = NULL;
    return new_node;
}

int is_bid_unique(blockchain_t* blockchain, char* bid)
{
    Node *node_temp = blockchain->head;
    while(node_temp != NULL)
    {
        Bid_t *current = node_temp->block;
        while (current != NULL)
        {
            if(_strcmp(bid, current->b_block) == 0)
            {
                printf("nok: this block already exists\n");
                return 0;
                }
            current = current->next;
        }
        node_temp = node_temp->next;
    }

    return 1;
}

void add_bid_to_all(blockchain_t* blockchain, char* bid)
{
    Node* node_temp = blockchain->head;

    while (node_temp != NULL)
    {
        Bid_t *new_bid = malloc(sizeof(Bid_t));
        _strcpy(new_bid->b_block, bid);
        new_bid->next = NULL;

        if(node_temp->block == NULL)
        {
            node_temp->block = new_bid;    
        } else
        {
            node_temp->block_tail->next = new_bid;
        }
        node_temp->block_tail = new_bid;
        node_temp->bids_in_use++;
        node_temp = node_temp->next;
    }
}

void add_bid(blockchain_t* blockchain, char* bid, int nid)
{
    Node* node_temp = blockchain->head;

    while (node_temp != NULL)
    {
        if (node_temp->nid == nid) {
            break;
        }
        node_temp = node_temp->next;
    }

    Bid_t *new_bid = malloc(sizeof(Bid_t));
    _strcpy(new_bid->b_block, bid);
    new_bid->next = NULL;

    if(node_temp->block == NULL)
    {
        node_temp->block = new_bid;    
    } else
    {
        node_temp->block_tail->next = new_bid;
    }
    node_temp->block_tail = new_bid;
    node_temp->bids_in_use++;
}

void find_new_bid_tail(Node* node_temp, Bid_t *bid_delete)
{ 
    Bid_t *bid_temp = node_temp->block;
    while(bid_temp->next->next != bid_delete)
    {
        bid_temp = bid_temp->next;
    }
    node_temp->block_tail = bid_temp->next;
}

void remove_bid(blockchain_t* blockchain, char* bid)
{
    Node* node_temp = blockchain->head;
    while(node_temp != NULL)
    {
        if(_strcmp(node_temp->block->b_block, bid) == 0)
        {
            //if the bid is the head and this is the only bid
            if(node_temp->block == node_temp->block_tail)
            {
            //this is the only bid
                free(node_temp->block);
                node_temp->block = NULL;
                node_temp->block_tail = NULL;
            } else
            {
                Bid_t *bid_delete = node_temp->block;
                node_temp->block = node_temp->block->next;
                free(bid_delete);
            }
        } else if(_strcmp(node_temp->block->next->b_block, bid) == 0 && node_temp->block->next == node_temp->block_tail)
        {
            //if the bid is the tail and there are just 2 bids in the list
            free(node_temp->block_tail);
            node_temp->block_tail = node_temp->block;
        } else
        {
            Bid_t *bid_temp = node_temp->block;
            Bid_t *bid_delete = NULL;
            while (bid_temp != NULL) {
            if (_strcmp(bid_temp->next->b_block, bid) == 0)
            {
                bid_delete = bid_temp->next;
                break;
            }
            bid_temp = bid_temp->next;
            }

            if(_strcmp(node_temp->block_tail->b_block, bid) == 0)
            {
                // if bid we are removing is the tail we need to reposition the tail
                find_new_bid_tail(node_temp, node_temp->block_tail);
            }

            if (bid_delete != NULL)
            {
            bid_temp->next = bid_delete->next;
            free(bid_delete);
            }
        }
        //Bid_t *block_temp = node_temp->block;
        node_temp->bids_in_use--;
        node_temp = node_temp->next;
    }
}

void find_new_tail(blockchain_t* blockchain, Node *node_delete)
{
    if(node_delete != NULL)
    {
        if(node_delete == blockchain->tail && node_delete == blockchain->head->next)
        {
            blockchain->tail = blockchain->head;
        } else if(node_delete == blockchain->tail && node_delete != blockchain->head->next)
        {
            Node *node_temp = blockchain->head;
            while(node_temp->next->next != node_delete)
            {
                node_temp = node_temp->next;
            }
            blockchain->tail = node_temp->next;
        }
    }
}

int remove_node(blockchain_t* blockchain, int nid) {
    if(blockchain->head == NULL)
    {
        return 1;
    } else if(blockchain->head->nid == nid)
    {
        if(blockchain->head == blockchain->tail)
        {
            free(blockchain->head);
            blockchain->head = NULL;
            blockchain->tail = NULL;
        } else
        {
            Node* node_temp = blockchain->head;
            blockchain->head = blockchain->head->next;
            free(node_temp);
        }
        blockchain->node_count--;
        return 0; // node is removed successfully
    } else 
    {
        Node* node_temp = blockchain->head;
        Node* node_delete = NULL;
        while (node_temp != NULL) {
            if (node_temp->next->nid == nid) {
                node_delete = node_temp->next;
                break;
            }
            node_temp = node_temp->next;
        }
        
        find_new_tail(blockchain, node_delete);

        if (node_delete != NULL) {
            node_temp->next = node_delete->next;

            free(node_delete);
            blockchain->node_count--;
            return 0; // node is removed successfully
        }
    }
    return 1; // node is not found
}

void del_linked_list(blockchain_t* blockchain) {
    if (blockchain == NULL) {
        return;
    }
    Node *temp = blockchain->head;
    while (temp != NULL) {
        Node* next = temp->next;
        Bid_t * temp_block = temp->block;
        while(temp_block != NULL)
        {
            Bid_t * next_block = temp_block->next;
            free(temp_block);
            temp_block = next_block;
        }
        free(temp);
        temp = next;
    }
/*
    Bid_t * temp_block = blockchain->master_block;
    while(temp_block != NULL)
    {
        Bid_t * next_block = temp_block->next;
        free(temp_block);
        temp_block = next_block;
    }*/
    blockchain->head = NULL;
    blockchain->tail = NULL;
}

void print_list(blockchain_t* blockchain)
//prints nodes and their blocks
{
    Node* temp_nid = blockchain->head;
    while(temp_nid != NULL) {
        
        _printf("%i:", temp_nid->nid);
        
        Bid_t* temp_bid = temp_nid->block;
        while(temp_bid != NULL)
        {
            _printf(" %s,", temp_bid->b_block);
            temp_bid = temp_bid->next;
        }
        _printf("\n");
        temp_nid = temp_nid->next;
    }
}

void print_nodes(blockchain_t* blockchain)
//prints nodes
{
    Node* temp = blockchain->head;
    while(temp != NULL) {
        _printf("%i:", temp->nid);
        _printf("\n");
        temp = temp->next;
    }
}

void sync_nodes(blockchain_t* blockchain)
{
    int found = 0;
    Node *verify_node = blockchain->head;
    while(verify_node != NULL)
    {
        Node *node_temp = blockchain->head;
        while(node_temp != NULL)
        {
            Bid_t *block_node = node_temp->block;
            while(block_node != NULL)
            {
                Bid_t *verify_block = verify_node->block;
                while(verify_block != NULL)
                {
                    if(_strcmp(verify_block->b_block, block_node->b_block) == 0)
                    {
                        found = 1;
                        break;
                    }
                    verify_block = verify_block->next;
                }
                if(found == 0)
                {
                    add_bid(blockchain, block_node->b_block, verify_node->nid);
                } else
                {
                    found = 0;
                }
                block_node = block_node->next;
            }
            node_temp = node_temp->next;
        }
        verify_node = verify_node->next;
    }
}