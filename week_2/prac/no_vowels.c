// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

void replace(int len, char c_arr[]);
void leetify(int c_index, char c_arr[]);

int main(int argc, string argv[])
{
    // if no args or more than one arg
    if (argc == 1 || argc > 2)
    {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }
    // replace vowels
    replace(strlen(argv[1]), argv[1]);
    printf("%s\n", argv[1]);
}

void replace(int len, char c_arr[])
{
    for (int i = 0; i < len; i++)
    {
        // destructively replace
        leetify(i, c_arr);
    }
}

void leetify(int c_index, char c_arr[])
{
    switch (c_arr[c_index])
    {
        case 'a':
            c_arr[c_index] = '6';
            break;
        case 'e':
            c_arr[c_index] = '3';
            break;
        case 'i':
            c_arr[c_index] = '1';
            break;
        case 'o':
            c_arr[c_index] = '0';
            break;
        case 'u':
            c_arr[c_index] = 'u';
            break;
        default:
            // do nothing
            break;
    }
}
