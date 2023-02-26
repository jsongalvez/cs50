#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool prime(int number);

int main(void)
{
    int min;

    // get input > 0
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    // get input >= minimum
    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    // check from primes between min and max
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    bool flag = true;
    // GCF can't be greater than sqrt of number
    for (int i = sqrt(number); i > 1; i--)
    {
        // any factors aside from 1 and number makes it non-prime
        if (number % i == 0)
        {
            flag = false;
            break;
        }
        else
        {
            flag = true;
        }
    }
    return flag;
}
