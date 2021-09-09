# my_blockchain


-> Check if there is a saved file
    -> Read content
        Text file
            • total number of nodes;
            • the list of blocks (array?) - in the order of creation;
            • whether it is synced or not;
            • list of nodes as nid, bid, sync, next pointer
                each node on a separate line?
                NID is an int
                    atoi <> itoa conversion
                BID is a string
            • total number of lines in the file is total number of nodes + 2
    -> fill the blockchain
        • Implemented as a single linked list
            • int nid
            • char **bid
            • int synced
            • next node pointer


-> Request a promptl
            • add node nid 
                add a nid identifier to the blockchain node.
                ------> what exactly is a node id <------
            • rm node nid
                remove nodes from the blockchain with a nid identifier. If nid is '*', then all nodes are impacted.
            • add block bid nid
                add a bid identifier block to nodes identified by nid. If nid is '*', then all nodes are impacted.
            • rm block bid
                remove the bid identified blocks from all nodes where these blocks are present.
            • ls
                list all nodes by their identifiers. The option -l attaches the blocks bid's associated with each node.
            • sync
                synchronize all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks.
            • quit
                save and leave the blockchain.


Success
    display "ok"
Fail
    "nok: info"
    Error messages:
        1: no more resources available on the computer [done]
        2: this node already exists
        3: this block already exists
        4: node doesn't exist [done]
        5: block doesn't exist
        6: command not found [done]


The blockchain prompt must display (see example below):
    a [ character
    a first letter that indicates the state of synchronization of the chain:
        "s" if the blockchain is synchronized
        "-" if the blockchain is not synchronized.
    n number of nodes in the chain.
    the "]> " string (with a space)


Example:
    $>my_blockhain
    [s0]> add node 12
    [s1]> add block 21 *
    [s1]> add node 13
    [-2]> sync
    [s2]> ls -l
    12: 21,
    13: 21,
    [s2]> quit


Allowed C-library functions:
    • malloc(3)
    • free(3)
    • printf(3)
    • write(2)
    • open(2)
    • read(2)
    • close(2)

Functions to Code
    - create node
    - add node to established block
    - create blockchain
    - remove node/ blockchain
    - sync_all_blockchains
    - prompt
    - print_to_screen
        - fx to output proper display such as [, ], nid, bid, etc
    

File content:
        Text file
            • total number of nodes;
            • the list of blocks (array?) - in the order of creation;
            • whether it is synced or not;
            • list of nodes as nid, bid, sync, next pointer
                each node on a separate line?
                NID is an int
                    atoi <> itoa conversion
                BID is a string
            • total number of lines in the file is total number of nodes + 2

First line -> Number of nodes, synced \n
Second line -> all blocks \n bid1,bid2,bid3,...\n
                        [[bid1],[bid2],[bid3]...]
NID,sync,pointer,bid1,bid2,bid3,...\n
BID\n
sync\n
Pointer\n

Node -> Node -> Node -> Node ->...
• block