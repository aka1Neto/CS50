// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27;

// Hash table

node *table[N];
int dictsize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashs = hash(word);
    node *temp = table[hashs];

    while(temp != NULL){
        if(strcasecmp(temp->word, word) == 0) return true;
        temp = temp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int length = strlen(word);
    int value = 0;
    for(int i = 0; i < length; i++){
        value += tolower(word[i]);
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL) return false;

    while(fscanf(dict, "%s\n", word) != EOF){
        int hashs = hash(word);
        node *temp = malloc(sizeof(node));

        strcpy(temp->word, word);

        temp->next = table[hashs];
        table[hashs] = temp;

        dictsize++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++){
        node *n = table[i];
        while(n != NULL){
            node *temp = n;
            n = n->next;
            free(temp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
