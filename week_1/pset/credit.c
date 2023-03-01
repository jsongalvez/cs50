#include <cs50.h>
#include <stdio.h>

#define min_digits 1000000000000 // 13 digits, floor
#define max_digits 9999999999999999 // 16 digits, ceiling
#define max_len 16 // for setting array to 16 digits
#define mii_len 2 // Major Industry Identifier (MII)

bool luhn(int id[], int len); // luhn's algorithm
void print_card_type(long card);
void split_to_array(long num, int arr[]); // stored from right to left
int card_type(int id[], int len);

enum card
{
    INVALID = 1,
    AMEX,
    VISA,
    MASTERCARD
};

int main(void)
{
    // Get input
    long id = 0;
    id = get_long("Number: ");

    // Output card type
    print_card_type(id);
}

void print_card_type(long id)
{
    // check id length
    int len = 0;
    // if 13 digits
    if (id < 10000000000000)
    {
        len = 13;
    }
    // if 14 digits
    else if (id < 100000000000000)
    {
        len = 14;
    }
    // if 15 digits
    else if (id < 1000000000000000)
    {
        len = 15;
    }
    // if 16 digits (default)
    else
    {
        len = 16;
    }

    // convert to array
    int id_arr[max_len];
    split_to_array(id, id_arr);

    switch (card_type(id_arr, len))
    {
        case INVALID:
            printf("INVALID\n");
            break;
        case AMEX:
            printf("AMEX\n");
            break;
        case VISA:
            printf("VISA\n");
            break;
        case MASTERCARD:
            printf("MASTERCARD\n");
            break;
        default:
            printf("UNKNOWN ERROR OCCURED\n");
            break;
    }
}

// store number from right to left
// helps in calculating luhn's algorithm
void split_to_array(long num, int arr[])
{
    int i = 0;
    for (long num_copy = num; num_copy > 0; num_copy /= 10, i++)
    {
        arr[i] = num_copy % 10; // get last digit
    }
}

// INVALID = 1 AMEX = 2 VISA = 3 MASTERCARD = 4
int card_type(int id[], int len)
{
    // mii[2]
    int mii[mii_len];

    // grab the first two numbers of array
    // note: array is id stored in reverse
    int j = 0;
    for (int i = len - 1; i > len - 1 - mii_len; i--)
    {
        mii[j] = id[i];
        j++;
    }

    // calculate luhn's algorithm if valid number
    bool valid = luhn(id, len);
    if (!valid) // if not valid number, then
    {
        return INVALID;
    }

    // check if AMEX: 34, 37
    //          VISA: 4,
    //          MASTERCARD: 51, 52, 53, 54 ,55

    // if AMEX
    if (mii[0] == 3)
    {
        if (mii[1] == 4 || mii[1] == 7)
        {
            return AMEX;
        }
    }
    // if VISA
    else if (mii[0] == 4)
    {
        return VISA;
    }
    // if MASTERCARD
    else if (mii[0] == 5)
    {
        if (mii[1] == 1 || mii[1] == 2 ||
            mii[1] == 3 || mii[1] == 4 ||
            mii[1] == 5)
        {
            return MASTERCARD;
        }
    }

    // default return value
    return INVALID;

}

// luhn's algorithm
bool luhn(int id[], int len)
{
    // 2 * every other number
    // sum of all resulting digits (split double digits)
    int sum = 0;
    int temp[2]; // used to store split values

    for (int i = 1; i < len; i += 2)
    {
        // if double digit, split to two
        if (2 * id[i] > 9)
        {
            split_to_array(2 * id[i], temp);
            sum += temp[0];
            sum += temp[1];
        }
        // if single digit
        else
        {
            sum += 2 * id[i];
        }
    }

    // add sum to the rest of the digits
    for (int i = 0; i < len; i += 2)
    {
        sum += id[i];
    }
    // if sum % 10 is 0, card is valid
    if (sum % 10 == 0)
    {
        return true;
    }
    // else, not a valid card
    else
    {
        return false;
    }

    // default return value
    return -1;
}
