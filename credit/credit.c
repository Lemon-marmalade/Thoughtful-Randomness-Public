#include <cs50.h>
#include <stdio.h>

int calculate_digit(long number);
int calculate_second_digit(long number);

int main(void)

{
    long number;
    // prompt user for string of numbers
    do
    {
        number = get_long("Number: ");
    }
    while(number < 0);
    number_og = number
    int digit = calculate_digit(number);
    int second_digit = calculate_second_digit(number);

    if((digit+second_digit) % 10 == 0)
    {
        if((number_og > 340000000000000 && number < 350000000000000)||(number > 370000000000000 && number < 380000000000000))
        {
            printf("AMEX\n");
        }
        else if(number_og > 5100000000000000 && number < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else if((number_og > 4000000000000 && number < 5000000000000)||(number > 4000000000000000 && number < 5000000000000000))
        {
            printf("VISA\n");
        }
         else
        {
        printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
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
    {
        for(; number > 0;)
        {
        digit = digit + number % 10;
        number = number / 10;
        }
        return digit;
    }
}
int calculate_second_digit(long number)
{
    int second_digit = 0;
    {
        {
        second_digit = second_digit + ((number % 10)*2);
        number = number / 10;
        }
        return second_digit;
    }
}
