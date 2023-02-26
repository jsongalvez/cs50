/**********
2/26/23
half

Author: Galvez, Jayson S.
**********/

#include <stdio.h>
#include <cs50.h>
#define DINERS 2


float calculate(float bill, float tax, float tip);
float calcTax(float bill, float tax);
float calcTip(float bill, float tax, float tip);

int main(void)
{
    // input bill, tax, tip (add tax to bill before tip)
    float bill = get_float("Bill before tax and tip: ");
    float tax = get_float("Sale Tax Percent: ");
    float tip = get_float("Tip percent: ");
    // calculate
    float total = calculate(bill, tax, tip);
    printf("You will owe $%.2f each!\n", total / DINERS);
}

// calculate total bill
float calculate(float bill, float tax, float tip)
{
    return bill + calcTax(bill, tax) + calcTip(bill, tax, tip);
}


float calcTax(float bill, float tax)
{
    return bill * tax / 100;
}

// calculates after bill and tax has been added
float calcTip(float bill, float tax, float tip)
{
    return (bill + calcTax(bill, tax)) * tip / 100;
}
