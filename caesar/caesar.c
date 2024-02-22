#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // check that there is one command argument that is a number
    if (argc != 2 || argv < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // prompt for plaintext
        // apply the key
        //output ciptertext
        printf("%s\n", argv[1]);
    }
}

