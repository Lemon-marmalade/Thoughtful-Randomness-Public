#include <cs50.h>
#include <stdio.h>

int main(void)

{
    int x;
    do
    {
         x = get_int("Change owed: ");
    }
    while (x < 1 );
     // write conditions
     if (x > 25)
     {
          int a = (x / 25);
          int b = (x % 25);

          if (b > 10)
          {
               int c = (b / 10)
               int d = (b % 10)
          }
          else if (b > 5 && b < 10)
          {
               int e = (b / 5)
               int f = (b % 5)
          }
          else if (b )

          printf("Minimum amount of coins: %i \n", x / 25);
     }
}
