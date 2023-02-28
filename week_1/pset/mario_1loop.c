/*********************
cs50x
02/28/23
Galvez, Jayson S.
mario.c

References:
- https://stackoverflow.com/questions/25829669/how-do-you-multiply-a-character-in-c-like-python
*********************/

#include <cs50.h> // get_int
#include <stdio.h> // printf
#include <string.h> // memset
#include <stdlib.h> // malloc

#define SPACE ' '
#define PYRA '#'

void pyramid(int layer);
void char_multiply(char c, int len);

int main(void)
{
    // ask for pyramid height (1-8)
    int layer = 0;
    do
    {
        layer = get_int("Height: ");
    }
    while (layer < 1 || layer > 8);

    // print loop pyramids
    pyramid(layer);
}

void pyramid(int layer)
{
    // single for-loop implementation
    for (int i = 1; i <= layer; i++)
    {
        // left pyramid
        char_multiply(SPACE, layer - i);
        char_multiply(PYRA, i);

        // gap
        printf("  ");

        // right pyramid
        char_multiply(PYRA, i);
        //char_multiply(SPACE, layer - i); // not needed visually

        // newline for next layer
        printf("\n");
    }
}

void char_multiply(char c, int len)
{
    len++; // account for null terminator '\0'
    char *str = (char *)malloc(len); // allocate a char array of size len
    memset(str, c, len - 1); // fill array with characters excluding null terminator
    str[len - 1] = '\0'; // set last index as null terminator
    printf("%s", str);

    free(str); // deallocate char array
}
