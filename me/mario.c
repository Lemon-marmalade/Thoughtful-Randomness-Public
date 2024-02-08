#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int n;
// rejects answers less than 1 or greater than 8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
// r for rows, s for spaces, b for blocks/hashes
    for (int r = 0; r < n; r++)
    {
        for (int s == (n - 1) ; s = 0; j--)
        {
            printf(" ");
        }
        for (int h = 0; h < n; h++)
        {
            printf("#");
        }
        printf("\n")
    }
}
