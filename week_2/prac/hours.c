#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

#define TOTAL 'T'
#define AVG 'A'

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != TOTAL && output != AVG);

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    float calculated_hours = 0;
    switch(output)
    {
        case TOTAL:
            for (int i = 0; i < weeks; i++)
            {
                calculated_hours += hours[i];
            }
            return calculated_hours;
            break;
        case AVG:
            for (int i = 0; i < weeks; i++)
            {
                calculated_hours += hours[i];
            }
            return calculated_hours / weeks;
            break;
        default:
            printf("Unkown error occured");
            return 100;
    }
}
