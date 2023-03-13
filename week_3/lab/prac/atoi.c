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

// Pops the last character recursively from right to left
// Popped character is converted to integer
int convert(string input)
{
    // get length of string
    int len = strlen(input);
    // make a copy
    string input_copy = input;
    // ascii 0-9 is 48 to 57
    // subtract ascii character by 48 to get integer equivalent
    int popped_number = (int) input_copy[len - 1] - ASCII_0;
    // delete last character
    input_copy[len - 1] = '\0';

    // recursive
    int new_popped_number = convert(input_copy);

    // add popped number by moving the tens place
    // of new popped number
    return 10 * new_popped_number + popped_number;
}
