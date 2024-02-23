#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string calculate_cipher(int key);

int main(int argc, string argv[])
{
    // check that there is one command argument that is a number
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for(int i = 0; i < strlen (argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
        printf("Usage: ./caesar key\n");
        return 1;
        }
        else
        {
        // prompt for plaintext
        string plaintext = get_string("plaintext:  ");
        int key = atoi(argv[1]);
        // apply the key
        string cipher = calculate_cipher(key);
        //output ciptertext
        printf("ciphertext: %s", cipher);
        }
    }
}

string calculate_cipher(int key)
{
    string cipher = argv[1];

    for(int i = 0; i < plain; i++)
    {
        argv[1][i] = argv[1][i] + key;
    }
    return cipher;
}

