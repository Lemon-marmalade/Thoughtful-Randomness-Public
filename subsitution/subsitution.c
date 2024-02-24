#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string calculate_cipher(int key, string plain);
char alpha[]={A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}
int main(int argc, string argv[])
{
    // check that there is one command argument that is a number
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // prompt for plaintext
    string plaintext = get_string("plaintext:  ");

    int key = atoi(argv[1]);

    // apply the key
    string cipher = calculate_cipher(key, plaintext);
    // output ciptertext
    printf("ciphertext: %s\n", cipher);
}

string calculate_cipher(int key, string plain)
{
    string cipher = plain;

    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            int n = (key + toupper(plain[i]) - 64) / 26;
            cipher[i] = cipher[i] + (key - 26 * n);
        }
    }
    return cipher;
}
