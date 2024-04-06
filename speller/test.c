#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char *word);

int main(void)
{
    char *word = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    int hash_value = hash(word);
    printf("%i\n", hash_value);
}

unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // this hash function will initialize the hashvalue to the numerical value of the first letter (1-26)
    int hash_value = toupper(word[0] + 1) - 'A';
    // if the word has more than 1 letter, it will multiply the previous hash value by 31 (an odd prime number in order to create more possibilities) before adding the next numerical value
    int word_length = strlen(word);
    if (word_length > 1)
    {
        for (int i = 1; i < word_length; i++)
        {
            hash_value = hash_value * 2 + (toupper(word[i] + 1)-'A');
        }
    }
    return hash_value;
}
