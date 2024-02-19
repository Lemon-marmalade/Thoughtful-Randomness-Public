#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_letters(string text);
int calculate_words(string text);
int calculate_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = calculate_letters(text);
    int words = calculate_words(text);
    int sentences = calculate_sentences(text);

    float index = 0.0588 * (letters * 100/(float)words) - 0.296 * (sentences * 100/(float)words) - 15.8;
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    {
        printf ("Grade 16+\n");
    }
    else
    {
        printf ("Grade %f\n", index);
    }
}
// prompt user for text
// count # of letters, wors, and sentences in text
// compute Coleman-Liau index
// print grade level

int calculate_letters(string text)
{
    int letters = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
            letters = letters + 1;
        }
    }
    return letters;
}
int calculate_words(string text)
{
    int words = 1;
    for(int i = 0; i < strlen(text); i++)
    {
        if(isspace(text[i]))
        {
            words = words + 1;
        }
    }
    return words;
}
int calculate_sentences(string text)
{
    int sentences = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(text[i]==46 || text[i]==77 || text[i]==33)
        {
            sentences = sentences + 1;
        }
    }
    return sentences;
}
