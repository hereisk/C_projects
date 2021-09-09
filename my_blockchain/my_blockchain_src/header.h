#ifndef HEADER_H
#define HEADER_H

#define QUIT_CMD "quit"
#define SYNC_CMD "sync"
#define LS_CMD "ls"
#define ADD_NODE_CMD "add node"
#define ADD_BLOCK_CMD "add block"
#define RM_NODE_CMD "rm node"
#define RM_BLOCK_CMD "rm block"
#define SAVED_FILE_PATH "my_blockchain_src/save"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_BIDS 10
#define BUFF_SIZE 2048

// linked_list.c
typedef struct bid_t {
    char b_block[MAX_BIDS];
    struct bid_t* next;
} Bid_t;

typedef struct node {
    int nid;
    int bids_in_use;
    Bid_t* block;
    Bid_t* block_tail;
    struct node* next;
} Node;

typedef struct blockchain_s {
    Node* head;
    Node* tail;
    int node_count;
} blockchain_t;

Node* create_node(blockchain_t* blockchain, int nid);
void print_list(blockchain_t* blockchain);
void del_linked_list(blockchain_t* blockchain);
void sync_nodes(blockchain_t* blockchain);
void fill_bid_list(blockchain_t* blockchain, int nid, char* bid);
void remove_bid(blockchain_t* blockchain, char* bid);
int remove_node(blockchain_t* blockchain, int nid);
int is_bid_unique(blockchain_t* blockchain, char* bid);
int is_nid_unique(blockchain_t* blockchain, int nid);
void add_bid_to_all(blockchain_t* blockchain, char* bid);
void print_nodes(blockchain_t* blockchain);
void add_bid(blockchain_t* blockchain, char* bid, int nid);

// auxilary.c
int _atoi(char *str);
int _printf(char* string, ...);
int _strlen(char *string);
void print_itoa(long number, int base);
int _strcmp(char *string1, char *string2);
char* _strdup(char *s1);
char* _strcpy(char *dest, const char *src);
int get_bid_nid(char *input, char *bid, char *nid);

//extract.c
void read_from_file(blockchain_t* blockchain);
void write_to_file(blockchain_t* blockchain);

// input.c

int sort_input(char *buf, blockchain_t *blockchain);
void display_prompt(char *state, blockchain_t *blockchain);
int read_input(blockchain_t *blockchain);
void request_input(blockchain_t *blockchain);
int is_nid_valid(char *nid);


#endif