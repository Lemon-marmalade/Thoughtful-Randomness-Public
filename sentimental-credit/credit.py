from cs50 import get_int

def main():
    #infinitely, ask for number until given positive
    while True:
        number = get_int("Number: ")
        if number >= 1:
            break
    digit = calculate_digit(number)
    #check given conditions of each type
    if digit % 10 == 0:
        if number in range(340000000000000, 350000000000000) or number in range(370000000000000, 380000000000000):
            print("AMEX")

        elif number in range(5100000000000000, 5600000000000000):
            print("MASTERCARD")

        elif number in range(4000000000000, 5000000000000) or number in range(4000000000000000, 5000000000000000):
            print("VISA")

        else:
            print("INVALID")

    else:
        print("INVALID")


def calculate_digit(number):
    digit = 0
    while number > 0:
        #let digit be the last digit of the number
        digit += number % 10
        #move on
        number = (number / 10) - (number % 10) / 10
        #add to digit, the next digit multiplied by 2's digits
        digit += ((number % 10) * 2) % 10 + ((number % 10) * 2) / 10 - (number % 10) / 10
        #move on
        number = (number / 10) - (number % 10) / 10
    return digit

main()
