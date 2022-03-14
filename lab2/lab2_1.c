#include <stdio.h>
#include <stdlib.h>
#define CHAR_SIZE 26

struct Trie{
    int isLeaf;
    struct Trie* character[CHAR_SIZE];
};

struct Trie* getNewNode(){
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++){
        node->character[i] = NULL;
    }

    return node;
}

void insert(struct Trie *core, char *str){
    struct Trie* current = core;
    
    while(*str){
        if (current->character[*str - 'a'] == NULL){
            current->character[*str - 'a'] = getNewNode();
        }
    
        current = current->character[*str - 'a'];

        str++;
    }

    current->isLeaf = 1;
}


int search(struct Trie *core, char *str){
    if (core == NULL){
        return 0;
    }

    struct Trie *current = core;
    while(*str){
        current = current->character[*str - 'a'];

        if (current == NULL){
            return 0;
        }
        str++;
    }
    return current->isLeaf;
}


int main(){

    struct Trie *core = getNewNode();

    return 0;
}