#include <cs50.h>
#include <stdio.h>

int main(int argc, int argv[])
{
    if (argc != 2 || argv < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        printf("%s\n", argv[1]);
    }
}
