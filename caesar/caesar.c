#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // check that there is one command argument that is a number
    if (argc == 2)
    {
        int key = atoi(argv[1]);
        printf("%i\n", key);
        // prompt for plaintext
        // apply the key
        //output ciptertext
    }
    else
    {

        printf("Usage: ./caesar key\n");
        return 1;
    }
}

