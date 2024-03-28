#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    // Create buffer for a block of data, and counter for # of images found
    uint8_t buffer[512];
    int image_count =0;
    char filename[8];
    // While there is still data left
    while (fread(buffer, 1, sizeof(buffer), card) == sizeof(buffer))
    {
        // Create JPEGS from data
        for (int i = 0; i < sizeof(buffer; i++))
        {
            // if buffer i to i+2 is equal to the given values, and if the intersection of buffer[i+3] and 1111 0000 is 1110 0000 (meaning buffer[i+3] must have first four bits of 1110)
            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
            {
                sprintf(output,"%03i.jpg",image_count);
            }
        }
    }

}
