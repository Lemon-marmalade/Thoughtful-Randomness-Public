#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string calculate_cipher(int key, string plain);

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
        string cipher = calculate_cipher(key, plaintext);
        //output ciptertext
        printf("ciphertext: %s\n", cipher);
        }
    }
}

string calculate_cipher(int key, string plain)
{
    string cipher = plain;

    for(int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            int n = key / 26;
            cipher[i] = cipher[i] + (key - 26 * n);
        }
    }
    return cipher;
}

