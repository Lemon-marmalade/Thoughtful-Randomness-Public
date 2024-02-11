#include <cs50.h>
#include <stdio.h>

int main(void)

{
     //prompt user for change owed, in cents
     do
     {
    int cents = get_int("Change owed: ");
     }
     while (cents < 1);
}
    // calculate how many quarters needed
    // sutract value of quarters from total change owed

    // calculate how many dimes needed for previous difference
    // subtract value of dimes from remaining cents

    // calculate how many nickels needed for previous difference
    // subtract value of nickels from remaining cents

    // calculate how many pennies needed
    // subtract value of pennies from remaining cents

    // add the number of quarters, dimes, nickels, and pennies
    // print the sum
