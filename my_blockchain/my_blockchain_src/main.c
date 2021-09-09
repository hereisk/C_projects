#include "header.h"

int main(void) {

    blockchain_t blockchain = {.head = NULL, .tail = NULL, .node_count = 0};// .master_block = NULL, .master_block_tail = NULL,, .unique_bids = 0

    int save_fd = open(SAVED_FILE_PATH, O_RDONLY);
    if(save_fd != -1)
    // to check if there is a backup
    // adn to recreate the blockchain from the file
    {
        close(save_fd);
        read_from_file(&blockchain);
    }
    request_input(&blockchain);

    return 0;
}
