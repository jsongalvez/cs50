#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define ASCII_0 48

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // ascii 0-9 is 48-57
    int len = strlen(input);
    if (len <= 0)
    {
        return 0;
    }

    // debugging
    printf("len: %i\n", len);

    // print current character
    string new_input = input;
    int number = (int) new_input[len - 1] - ASCII_0;
    // delete last character
    new_input[len - 1] = '\0';

    // recursive
    int new_number = convert(new_input);

    return 10 * new_number + number;
}
