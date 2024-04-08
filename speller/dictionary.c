// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1973;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    for (node *n = table[hash(word)]; n != NULL; n = n->next)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hash_value = toupper(word[0] + 1) - 'A';
    int word_length = strlen(word);
    if (word_length > 1)
    {
        for (int i = 1; i < word_length; i = i + 2)
        {
            hash_value = hash_value * 2 + (toupper(word[i] + 1)-'A');
            if ((i + 1) < word_length )
            {
                if (hash_value % 2 != 0)
                {
                    hash_value = (hash_value + 1) / 2 + (toupper(word[i + 1] + 1)-'A');
                }
                else
                {
                    hash_value = hash_value / 2 + (toupper(word[i + 1] + 1)-'A');
                }
            }
        }
    }
    return hash_value;
}

int wordcount = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // create temporary string for loading words
    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        return false;
    }
    // read each word(aka line) in file (scan string and set it as a word) until end of file
    while (fscanf(source, "%s", word) == 1)
    {
        // create a new node and copy word into that node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word);
        // hash the word to obtain hash value
        int hash_value = hash(word);
        // if word is first of its hash value
        if (table[hash_value] == NULL)
        {
            new_node->next = NULL;
        }
        // if there is another word already at this index, prepend the new word in front of pre-exisitng head
        else
        {
            new_node->next = table[hash_value];
        }
        // set the new node as the new head in this index
        table[hash_value] = new_node;
        // keep track of how many words have been hashed for the size function
        wordcount++;
    }
    // close dictionary file and free memory
    fclose(source);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // for all buckets
    for (int i = 0; i < N; i++)
    {
        // while there is something in the bucket, free each node
       node *to_free = NULL;
       node *waiting_free = table[i];

        while (waiting_free != NULL)
        {
            to_free = waiting_free;
            waiting_free = waiting_free->next;
            free(to_free);
        }
    }
    return true;
}
