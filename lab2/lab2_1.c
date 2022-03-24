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

// Returns 1 if a given Trie node has any children
int hasChildren(struct Trie* curr){
    for (int i = 0; i < CHAR_SIZE; i++){
        if (curr->character[i]) {
            return 1;
        }
    }
 
    return 0;
}

int deletion(struct Trie **curr, char* str){
    // return 0 if Trie is empty
    if (*curr == NULL) {
        return 0;
    }
 
    // if the end of the string is not reached
    if (*str){
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
                (*curr)->isLeaf == 0){
            if (!hasChildren(*curr)){
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else {
                return 0;
            }
        }
    }
 
    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf){
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr)){
            free(*curr);    // delete the current node
            (*curr) = NULL;
            return 1;       // delete the non-leaf parent nodes
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0;       // don't delete its parent nodes
        }
    }
 
    return 0;
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