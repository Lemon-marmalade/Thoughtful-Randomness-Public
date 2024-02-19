#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_letters(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = calculate_letters(text);
    printf("%i", letters);
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

