/**
 * cs50x
 * March 5, 2023
 * Galvez, Jayson S.
 * readability.c
*/

#include <cs50.h> // get_string, bool, string
#include <stdio.h> // printf
#include <ctype.h> // isalpha, isspace
#include <string.h> // strlen
#include <math.h> // round

void measure_text(string s, int *words, int *sentences, int *letters);
bool is_sentence_end(char c);
void print_grade(int index);

int main(void)
{
    string text = get_string("Text: ");

    // measure the amount of words, sentences, and letters in the text
    int words = 0, sentences = 0, letters = 0;
    measure_text(text, &words, &sentences, &letters);

    // get average number of letters
    float L = (float) letters / words * 100;
    // get average number of sentences
    float S = (float) sentences / words * 100;
    // calculate coleman-liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    // print grade
    print_grade(index);
}

void measure_text(string s, int *words, int *sentences, int *letters)
{
    int len = strlen(s);
    *words = 0, *sentences = 0, *letters = 0;
    bool word_flag = true, sentence_flag = true;
    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        // count letters
        if (isalpha(c))
        {
            *letters += 1;
        }
        // count words (naive)
        if (isalpha(c) && word_flag == true)
        {
            *words += 1;
            word_flag = false;
        }
        // count senctence
        else if (is_sentence_end(c) && sentence_flag == true)
        {
            *sentences += 1;
            sentence_flag = false;
        }

        // reset word flag at space char
        else if (isspace(c))
        {
            word_flag = true;
        }
        // reset sentence flag at non-punctuation char
        else if (!is_sentence_end(c) && sentence_flag == false)
        {
            sentence_flag = true;
        }
    }
}

bool is_sentence_end(char c)
{
    return c == '.' || c == '?' || c == '!';
}

void print_grade(int index)
{
    if (index > 16)
    {
        printf("Grade 16+");
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", index);
    }
    printf("\n");
}
