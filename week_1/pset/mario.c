/*********************
cs50x
02/28/23
Galvez, Jayson S.
mario.c
*********************/

#include <cs50.h>
#include <stdio.h>
#define BLANK " "
#define PYRA "#"
void pyramid(int layer);

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
    // layer by layer, starting from the top
    for (int h = layer - 1; h >= 0; h--)
    {
        // left side
        for (int w = 0; w < layer; w++)
        {
            // if w < h, print space
            if (w < h)
            {
                printf(BLANK);
            }
            // if w >= h, print pyramid
            else
            {
                printf(PYRA);
            }
        }

        // middle
        printf("  ");

        // right side
        for (int w = layer - 1; w >= 0; w--)
        {
            // if w < h, print space
            if (w < h)
            {
                printf("");
            }
            // if w >= h, print pyramid
            else
            {
                printf(PYRA);
            }
        }

        // newline for next layer
        printf("\n");
    }
}
