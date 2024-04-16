
def main():
    text = input("Text: ")

    letters = calculate_letters(text)
    words = calculate_words(text)
    sentences = calculate_sentences(text)

    index = 0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8

    if index < 1:
        print("Before Grade 1")

    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")

def calculate_letters(text):
    letters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1
    return letters

def calculate_words(text):
    words = 1
    for i in range(len(text)):
        if text[i].isspace():
            words += 1
    return words

def calculate_sentences(text):
    sentences = 0
    for i in range(len(text)):
        character = ord(text[i])
        if character == 46 or charactor == 63 or character == 33:
            sentences += 1
    return sentences

main()
