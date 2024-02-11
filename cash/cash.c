#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);

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
     // calculate how many dimes needed for previous difference
     int dimes = calculate_dimes(cents);
    // subtract value of dimes from remaining cents
     cents = cents- (dimes * 10);
    // calculate how many nickels needed for previous difference
    // subtract value of nickels from remaining cents

    // calculate how many pennies needed
    // subtract value of pennies from remaining cents

    // add the number of quarters, dimes, nickels, and pennies
    // print the sum

     printf("%i \n", quarters + dimes);
}


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


     int calculate_dimes(int cents)
     {
    // calculate how many dimes needed
    int dimes = 0;

    while (cents >= 10)
    {
     dimes++;
     cents = cents - 10;
    }
    return dimes;
     }
