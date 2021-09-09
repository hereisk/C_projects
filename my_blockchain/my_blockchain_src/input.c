#include "header.h"

int check_sync(blockchain_t* blockchain)
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
                    return 0;
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
    return 1;
}

int is_nid_valid(char *nid)
{
    int index = 0;
    while(nid[index] != '\0')
    {
        if(nid[index] < '0' || nid[index] > '9')
        {
            return 0;
        }
        index++;
    }
    return 1;
}

int _if_add_block(char *user_input, char *add_block_cmd)
{
    int i;
    for(i = 0; user_input[i] && add_block_cmd[i] && user_input[i] == add_block_cmd[i]; i++);
    if(i == 9)
    {
      return 1;
    }
    return 0;
}

int _if_add_node(char *user_input, char *add_node_cmd)
{
    int i;
    for(i = 0; user_input[i] && add_node_cmd[i] && user_input[i] == add_node_cmd[i]; i++);
    if(i == 8)
    {
      return 1;
    }
    return 0;
}

int _if_rm_block(char *user_input, char *rm_block_cmd)
{
    int i;
    for(i = 0; user_input[i] && rm_block_cmd[i] && user_input[i] == rm_block_cmd[i]; i++);
    if(i == 8)
    {
      return 1;
    }
    return 0;
}

int _if_rm_node(char *user_input, char *rm_node_cmd)
{
    int i;
    for(i = 0; user_input[i] && rm_node_cmd[i] && user_input[i] == rm_node_cmd[i]; i++);
    if(i == 7)
    {
      return 1;
    }
    return 0;
}

char eval_state(blockchain_t* blockchain)
// for each node check if BID list includes all bids from the master list
// if it does, then node.sync = 1
// trailing sum of all node.sync
// check is the trailing sum of all node.sync == total node count
// if so, return 's'
// else, return '-'

{
    if(check_sync(blockchain))
    {
        return 's';
    } else
    {
        return '-';
    }
}

int sort_input(char *buf, blockchain_t *blockchain)
{
    int word_count = 1;
    
    for(int i = 0; buf[i] != '\0'; i++)
    {
        if(buf[i] == ' ')
        {
            word_count++;
        }
    }

    if(word_count == 1)
    {
        if(!_strcmp(buf, QUIT_CMD))
        {
            write_to_file(blockchain);
            del_linked_list(blockchain);
            return 0;
        } else if(!_strcmp(buf, SYNC_CMD))
        {
            sync_nodes(blockchain);
        } else if(!_strcmp(buf, "ls"))
        {
            print_nodes(blockchain);
        } else
        {
            _printf("nok: command not found\n");
        }
        return 1;
    } else if(word_count == 2)
    {
        if(!_strcmp(buf, "ls -l"))
        {
            print_list(blockchain);
        } else
        {
            _printf("nok: command not found\n");
        }
        return 1;
    } else if(word_count == 3)
    {
        if(_if_add_node(buf, ADD_NODE_CMD))
        {
            char *nid = &buf[9];
            if(is_nid_valid(nid))
            {
                if(is_nid_unique(blockchain, _atoi(nid)))
                {
                    create_node(blockchain, _atoi(nid));
                } else
                {
                    _printf("nok: this node already exists\n");
                }
            } else
            {
                _printf("nok: nid is not valid\n");
            }
            
        } else if(_if_rm_node(buf, RM_NODE_CMD))
        {
            char *nid = &buf[8];
            if(remove_node(blockchain, _atoi(nid)))
            {
                _printf("nok: node doesn't exist\n");
            }
        }  else if(_if_rm_block(buf, RM_BLOCK_CMD))
        {
            char *bid = &buf[9];
            remove_bid(blockchain, bid);
        } else
        {
            _printf("nok: command not found\n");
        }
        return 1;
    } else if(word_count == 4)
    {
        if(_if_add_block(buf, ADD_BLOCK_CMD))
        {
            char bid[MAX_BIDS];
            char nid[10];
            get_bid_nid(buf, bid, nid);
            if(is_bid_unique(blockchain, bid))
            {
                if(nid[0] == '*')
                {
                    //all nodes are affected
                    add_bid_to_all(blockchain, bid);
                } else
                {
                    if(is_nid_valid(nid))
                    {
                        // check if nid is valid and exist, add bid to nid
                        if(!is_nid_unique(blockchain, _atoi(nid)))
                        {
                            add_bid(blockchain, bid, _atoi(nid));
                        } else
                        {
                            _printf("nok: nid doesn't exist\n");
                        }
                    }
                }
            } 
        } else
        {
            _printf("nok: command not found\n");
        } 
        return 1;
    } else
    {
        _printf("nok: command not found\n");
        return 1;
    }
    /*
        • add node nid
        • add block bid nid 
        • rm node nid
        • rm block bid
        • ls
        • sync
        • quit
    */
}

void display_prompt(char *state, blockchain_t *blockchain)
{
    _printf("[%c%i]> ", *state, (*blockchain).node_count);
}

int read_input(blockchain_t *blockchain)
{
    char buf[255];
    int bytes = read(0, buf, sizeof(buf));
    buf[bytes - 1] = '\0';

    return sort_input(buf, blockchain);
}

void request_input(blockchain_t *blockchain) // state, node_count, saved_fd
{
    char state;
    // while the input is not QUIT run display_prompt + sort the input
    do
    {
        state = eval_state(blockchain); // this needs to be redone to check if synced or not; eval_state -> check_if_synced
        display_prompt(&state, blockchain);
    } while (read_input(blockchain));

}
// [s0]> 
/*
-> prompt
-> figure out the input
-> run the command
    -> create a node
    -> create a block
*/ 
