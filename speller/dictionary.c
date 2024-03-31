// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return 1;
    }
    char word = [LENGTH + 1];
    // read each word/line in file (scan string and set it as a word) until end of file
    while (fscanf(source, %s, word) != EOF)
    {
        // create a new node and copy word into that node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return 1;
        }
        strcpy(new->word,word);
        // hash the word to obtain hash value
        // insert the new node into the hash table according to its hash value
    }
    // add each word read. to the hash table
    // close dictionary file
    fclose(source);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
