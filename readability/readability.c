#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_letters(string text);
int calculate_words(string text);
int calculate_sentences(string text);

int main(void)
{
    // prompt user for text and do calculations for variables
    string text = get_string("Text: ");

    int letters = calculate_letters(text);
    int words = calculate_words(text);
    int sentences = calculate_sentences(text);
    // Compute index
    float index = 0.0588 * (letters * 100 / (float) words) - 0.296 * (sentences * 100 / (float) words) - 15.8;
    // print different outputs based on conditions
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int grade = round(index);
        printf("Grade %i\n", grade);
    }
}

// calculate letters by using isalpha function in loop
int calculate_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters = letters + 1;
        }
    }
    return letters;
}
// calculate word by finding spaces and adding 1
int calculate_words(string text)
{
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            words = words + 1;
        }
    }
    return words;
}
// calculate sentences by checking for periods, question marks, and excalamtion points
int calculate_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 46 || text[i] == 63 || text[i] == 33)
        {
            sentences = sentences + 1;
        }
    }
    return sentences;
}
