#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);

int main(void)

{
     //prompt user for change owed, in cents
     int cents;
     do
     {
    cents = get_int("Change owed: ");
     }
     while (cents < 0);
     // calculate how many quarters needed
     int quarters = calculate_quarters(cents);
     // subtract value of quarters from cents
     cents = cents- (quarters * 25);

     printf("%i \n", quarters);
}
    // calculate how many dimes needed for previous difference
    // subtract value of dimes from remaining cents

    // calculate how many nickels needed for previous difference
    // subtract value of nickels from remaining cents

    // calculate how many pennies needed
    // subtract value of pennies from remaining cents

    // add the number of quarters, dimes, nickels, and pennies
    // print the sum


     int calculate_quarters(int cents)
     {
    // calculate how many quarters needed
    int quarters = 0;

    while (cents >= 25)
    {
     quarters++;
     cents = cents - 25;
    }
    return quarters;
     }

