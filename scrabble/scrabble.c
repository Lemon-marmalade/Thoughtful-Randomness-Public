#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int calculate_score(string word);
// array for points
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    do
    {
    string first_word = get_string( "Player 1: ");
    }
    while(first_word)
    
    string second_word = get_string( "Player 2: ");

    int score1 = calculate_score(first_word);

    int score2 = calculate_score(first_word);

    if(score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if(score1 < score2)
    {
        printf("Player s wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
// prompt usuers for input
// assign numbers to each letter by converting ascii of capital to array of points
// compute score of each word
// print winner based on which score is higher


int calculate_score(string word)
{
    int score = 0;

    for(int i = 0; i < strlen(word); i++)
    {
        score = score + (toupper(word[i])-65);
    }
    return score;
}
