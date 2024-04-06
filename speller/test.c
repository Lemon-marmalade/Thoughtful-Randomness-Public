#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
unsigned int hash(const char *word);

unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // this hash function will initialize the hashvalue to the numerical value of the first letter (0-25)
    int hash_value = toupper(word[0]) - 'A';
    // if the word has more than 1 letter, it will multiply the previous hash value by 31 (an odd prime number in order to create more possibilities) before adding the next numerical value
    int word_length = strlen(word);
    if (word_length > 2)
    {
        for (int i = 1; i < word_length; i++)
        {
            hash_value = hash_value * 31 + (toupper(word[i])-'A');
        }
    }

}
