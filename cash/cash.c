#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)

{
    // prompt user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    // calculate how many quarters and subtracts from cents
    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);
    // calculate how many dimes needed for previous difference and subtract
    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);
    // calculate how many nickels needed for previous difference and subtract
    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);
    // calculate how many pennies needed and subtract
    int pennies = calculate_pennies(cents);
    cents = cents - pennies;
    // print sum
    printf("%i \n", quarters + dimes + nickels + pennies);
}

int calculate_quarters(int cents)
 {   // calculate how many quarters needed
    int quarters = 0;
    for(; cents >= 25; quarters++)
    {
        cents = cents - 25;
    }
 return quarters;
 }
int calculate_dimes(int cents)
{
    // calculate how many dimes needed
   int dimes = 0;
    for(; cents >= 10; dimes++)
    {
        cents = cents - 10;
    }
 return dimes;
}

int calculate_nickels(int cents)
{
    // calculate how many nickels needed
    int nickels = 0;
    for(; cents >= 5; nickels++)
    {
        cents = cents - 5;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    // calculate how many nickels needed
    int pennies = 0;
     for(; cents >= 1; pennies++)
    {
        cents = cents - 1;
    }
    return pennies;
}
