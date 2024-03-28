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
    // Create buffer for a block of data
    uint8_t buffer[512];
    // While there is still data left
    while (fread(buffer, 1, sizeof(buffer), card) == sizeof(buffer))
    {
        // Create JPEGS from data
        for (int i = 0; i < sizeof(buffer; i++))
        {
            if (buffer[i] == "0xff" && buffer[i + 1] == "0xd8" && buffer[i + 2] == "0xff")
            for (int a = 0; a < "0xee")
            {
                if (a == buffer[i + 4])
                {
                    
                }
            }
        }
    }

}
