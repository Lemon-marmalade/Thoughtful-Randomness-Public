from cs50 import get_int

def main():
    while True:
        number = get_int("Number: ")
        if number >= 1:
            break
    digit = calculate_digit(number)
    if digit % 10 == 0:
        if number in range(340000000000000,350000000000000 or number in range(370000000000000, 380000000000000)
            print("AMEX")

        elif number in range(5100000000000000 and number < 5600000000000000:
            print("MASTERCARD")

        elif (number > 4000000000000 and number < 5000000000000) or (number > 4000000000000000 and number < 5000000000000000):
            print("VISA")

        else:
            print("INVALID")

    else:
        print("INVALID")


def calculate_digit(number):
    digit = 0
    while number > 0:
        digit = digit + number % 10
        number = number / 10

        digit = digit + (((number % 10) * 2) % 10 + ((number % 10) * 2) / 10)
        number = number / 10
    return digit

main()
