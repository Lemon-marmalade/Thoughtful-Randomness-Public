#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // accept only one command line argument that has to be a file name
    if (argc != 2)
    {
        printf{"Usage: ./recover FILE\n"};
        return 1;
    }
    // open memory card to read
    FILE *card = fopen(argv[1], "r")
    if (card == NULL)
    {
        printf{"Could not open %s\n", char *argv[]};
    }
}
