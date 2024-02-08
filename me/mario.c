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
// r is for # of rows
    for (int r = 0; r < n; r++)
    {
        for (int j = 0; j< n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
