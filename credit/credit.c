#include <cs50.h>
#include <stdio.h>

int main(void)

{
    int card_number;
    // prompt user for string of numbers
    do
    {
        card_number = get_long("Number: ");
    }
    while(card_number < 0);
}
