#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string calculate_cipher(string key, string plain);
int main(int argc, string argv[])
{
    // check that there is one command argument that is a number
    string key = argv[1];
    int length = strlen(argv[1]);

    if (argc != 2)
    {
        printf("Usage: ./subsitution key\n");
        return 1;
    }
    else if(length != 26)
    {
        printf("Key must contain 26 distinct characters\n");
        return 1;
    }
    for (int a = 0; a < length; a++)
    {
        for (int b = 1; b < length; b++)
        {
            for (int c = a + b; c < length; c++)
            {
                if (key[a] == key[c])
                {
                    printf("Key must contain 26 distinct characters\n");
                    return 1;
                }
            }
        }
    }

    }
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./subsitution key\n");
            return 1;
        }
    }
    // prompt for plaintext
    string plaintext = get_string("plaintext:  ");

    // apply the key
    string cipher = calculate_cipher(argv[1], plaintext);
    // output ciptertext
    printf("ciphertext: %s\n", cipher);
}

string calculate_cipher(string key, string plain)
{
    string cipher = plain;

    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            int n = toupper(plain[i]) - 65;
            if (isupper(plain[i]))
            {
                cipher[i] = toupper(key[n]);
            }
            else
            {
                cipher[i] = tolower(key[n]);
            }
        }
    }
    return cipher;
}
