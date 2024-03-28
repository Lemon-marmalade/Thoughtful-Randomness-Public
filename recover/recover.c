#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // accept only one command line argument that has to be a file name
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // open memory card to read
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }
    // Create buffer for a block of data
    uint8_t buffer[512];
    // While there is still data left
    while (fread(buffer, 1, 512, card) == 512)
    // Create JPEGS from data
}