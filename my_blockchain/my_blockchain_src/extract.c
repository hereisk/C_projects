#include "header.h"

void read_from_file(blockchain_t* blockchain)
{
    int save_fd = open(SAVED_FILE_PATH, O_RDONLY);
    read(save_fd, &blockchain->node_count, sizeof(int));

    for(int i = 0; i < blockchain->node_count; i++)
    {
        Node *new_node = malloc(sizeof(Node));
        read(save_fd, &new_node->nid, sizeof(int));
        read(save_fd, &new_node->bids_in_use, sizeof(int));
        if (blockchain->head == NULL)
        {
            blockchain->head = new_node;
            blockchain->tail = new_node;
        } else
        {
            blockchain->tail->next = new_node;
            blockchain->tail = new_node;
        }
        new_node->next = NULL;
        new_node->block = NULL;
        new_node->block_tail = NULL;

        for(int i = 0; i < new_node->bids_in_use; i++)
        {
            Bid_t *new_bid = malloc(sizeof(Bid_t));

            read(save_fd, &new_bid->b_block, MAX_BIDS);
            new_bid->next = NULL;
            if(new_node->block == NULL)
            {
                new_node->block = new_bid;    
            } else
            {
                new_node->block_tail->next = new_bid;
            }
                new_node->block_tail = new_bid;
            }
    }
    
}

void write_to_file(blockchain_t* blockchain)
{
    int save_fd = open(SAVED_FILE_PATH, O_RDONLY);
    if(save_fd != -1)
    {
        //if there is a saved file, then remove it;
        remove(SAVED_FILE_PATH);
    }
    close(save_fd);

    save_fd = open(SAVED_FILE_PATH, O_CREAT|O_WRONLY|O_TRUNC, 0444);

    write(save_fd, &blockchain->node_count, sizeof(int));
    Node* temp_nid = blockchain->head;
    while(temp_nid != NULL) {
        
        write(save_fd, &temp_nid->nid, sizeof(int));
        write(save_fd, &temp_nid->bids_in_use, sizeof(int));

        Bid_t* temp_bid = temp_nid->block;
        while(temp_bid != NULL)
        {
            write(save_fd, &temp_bid->b_block, MAX_BIDS);
            temp_bid = temp_bid->next;
        }
        temp_nid = temp_nid->next;
    }
}