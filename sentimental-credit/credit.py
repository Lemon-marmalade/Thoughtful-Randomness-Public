from cs50 import get_int

def main()
    while True:
        number = get_int("Number: ")
        if number >= 1:
            break
        

def calculate_digit(number)
    digit = 0
    while number > 0:
        digit = digit + number % 10
        number = number / 10

        digit = digit + (((number % 10) * 2) % 10 + ((number % 10) * 2) / 10)
        number = number / 10
    return digit


