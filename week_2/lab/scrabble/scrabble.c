#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define ASCII_UPPERCASE 65    // 'A' starts at 65

// Points assigned to each letter of the alphabet
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 == score2)
    {
        printf("Tie!");
    }
    else
    {
        printf("Player 2 wins!");
    }
    printf("\n");
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    // get length of string
    int len = strlen(word);

    // convert to uppercase (65)
    // uppercase - 65 as index
    // get sum of points
    int sum = 0;
    for (int i = 0, index = 0; i < len; i++)
    {
        if (isalpha(word[i]))
        {
            index = (int) toupper(word[i]) - ASCII_UPPERCASE;
            sum += POINTS[index];
        }
    }

    return sum;
}
