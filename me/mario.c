#include <stdio.h>
#include <cs50.h>

int main (void);

    int n;
// rejects answers less than 1 or greater than 8
    do {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
// r for rows, l for row #, b for blocks/hashes
    for (int r = 1; r <= n; r++)

    {
    for(int s = 1; s <= (n-r); s++)
     {
         printf(" ");
     }
     for(int b = 1; b<= r; b++)
    {
         printf("#");
     }
     printf("\n");
    }
