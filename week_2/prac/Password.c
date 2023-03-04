/**
 * cs50x
 * 03/04/23
 * Galvez, Jayson S.
 * password.c
*/

// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define PASS_CHAR password[i]

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
    int len = strlen(password);
    int up = 0, low = 0, num = 0, sym = 0;
    for (int i = 0; i < len; i++)
    {
        if (islower(PASS_CHAR))
        {
            up++;
        }
        else if (isdigit(PASS_CHAR))
        {
            num++;
        }
        else if (isupper(PASS_CHAR))
        {
            low++;
        }
        else if (ispunct(PASS_CHAR))
        {
            sym++;
        }
    }
    return (up > 0 && low > 0 && num && sym > 0) ? true : false;
}
