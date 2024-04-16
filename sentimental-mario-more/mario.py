from cs50 import get_int
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break
    space = height
    block = 1
for i in range(height):
    print(" " * space + "#" * block + "  " + "#" * block)
    space -= 1
    block += 1
