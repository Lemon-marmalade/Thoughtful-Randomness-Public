#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    // rejects answers less than 1
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // r for rows, l for row #, b for # of blocks/hashes for row
    for (int r = 1; r <= n; r++)

    {
        for (int s = 1; s <= (n - r); s++)
        {
            printf(" ");
        }
        for (int b = 1; b <= r; b++)
        {
            printf("#");
        }
        printf("\n");
    }
}
