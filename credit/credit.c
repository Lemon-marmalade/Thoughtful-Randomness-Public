#include <cs50.h>
#include <stdio.h>

int calculate_digit(long number);

int main(void)

{
    int number;
    // prompt user for string of numbers
    do
    {
        number = get_long("Number: ");
    }
    while(number < 0);
    int digit = calculate_digit(number);

    if(digit == 20)
    {
        printf("valid");
    }
    else
    {
        printf("invalid");
    }
}

// get and record values of every other value starting from last
    // use modulo to get remainder (aka last digit)
    // add last digit to sum
    // divide by 10

// get and record values of every other value starting from second last
    //use modulo to get remainder (second last digit from first number)
    // add last digit times 2 to the sum
    // divide by 10

// repeat until all numbers have been included
    // when number < 1
int calculate_digit(long number)
{
    int digit = 0;
    for(; number < 0;)
    {
    int digit = int digit + number % 10
    number = number / 10

    int digit = int digit + ((number % 10)*2)
    number = number / 10
    }
}
