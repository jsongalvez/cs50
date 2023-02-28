/***********************
cs50x
02/28/23
Galvez, Jayson S.
hello.c
***********************/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get string input
    string name = get_string("What is your name? ");
    // Output string
    printf("Hi %s\n", name);
}
