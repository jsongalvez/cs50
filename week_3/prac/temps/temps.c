    /**
     * cs50x
     * March 13, 2023 - March 16, 2023
     * Galvez, Jayson S.
     * temps.c
     *
     * Task is to create the sort_cities function
     * Implemented using merge sort
    */

    // Practice working with structs
    // Practice applying sorting algorithms

    #include <cs50.h>
    #include <stdio.h>
    #include <math.h>

    #define NUM_CITIES 10

    typedef struct
    {
        string city;
        int temp;
    }
    avg_temp;

    avg_temp temps[NUM_CITIES];

    void sort_cities(void);
    void merge_sort(avg_temp arr[], int start, int end);

    int main(void)
    {
        temps[0].city = "Austin";
        temps[0].temp = 97;

        temps[1].city = "Boston";
        temps[1].temp = 82;

        temps[2].city = "Chicago";
        temps[2].temp = 85;

        temps[3].city = "Denver";
        temps[3].temp = 90;

        temps[4].city = "Las Vegas";
        temps[4].temp = 105;

        temps[5].city = "Los Angeles";
        temps[5].temp = 82;

        temps[6].city = "Miami";
        temps[6].temp = 97;

        temps[7].city = "New York";
        temps[7].temp = 85;

        temps[8].city = "Phoenix";
        temps[8].temp = 107;

        temps[9].city = "San Francisco";
        temps[9].temp = 66;

        sort_cities();

        printf("\nAverage July Temperatures by City\n\n");

        for (int i = 0; i < NUM_CITIES; i++)
        {
            printf("%s: %i\n", temps[i].city, temps[i].temp);
        }
    }

    // TODO: Sort cities by temperature in descending order
    void sort_cities(void)
    {
        merge_sort(temps, 0, NUM_CITIES - 1);
    }

    void merge_sort(avg_temp arr[], int start, int end)
    {
        // base case
        // when it cannot be divided anymore
        int len = end - start;
        if (len <= 0)
        {
            return;
        }

        // calculate array lengths
        int arr_len = len + 1;
        int arr_len_left = ceil((float) arr_len / 2); // left side is equal or 1 unit larger
        int arr_len_right = arr_len - arr_len_left;

        // calculate indices for left side
        int start_left = start;
        int end_left = start_left + (end - start_left) / 2; // left side grabs half or 1 unit extra
        
        // calculate indices for right side
        int start_right = end_left + 1;
        int end_right = end;

        // left & right storage for this recursion
        avg_temp arr_left[arr_len_left], arr_right[arr_len_right];

        // copy to left & right
        for (int i = 0, j = 0; i < arr_len; i++)
        {
            // left
            if (i < arr_len_left) // copies half or 1 unit extra
            {
                arr_left[i] = arr[i];
            }
            //right
            else // copy the rest to the other side
            {
                arr_right[j] = arr[i];
                j++;
            }
        }

        // recursive left half
        merge_sort(arr_left, start_left, end_left);

        // recursive right half
        merge_sort(arr_right, start_right, end_right);

        // compare both sides (descending)
        for (int i = 0, i_l = 0, i_r = 0; i < arr_len; i++)
        {
            // if left empty, copy right
            if (i_l >= arr_len_left)
            {
                arr[i] = arr_right[i_r];
                i_r++;
            }
            // elif right empty, copy left
            else if (i_r >= arr_len_right)
            {

                arr[i] = arr_left[i_l];
                i_l++;
            }
            // elif left temp is greater, copy left
            else if (arr_left[i_l].temp > arr_right[i_r].temp)
            {
                arr[i] = arr_left[i_l];
                i_l++;
            }
            // else right temp is greater or equal, copy right
            else
            {
                arr[i] = arr_right[i_r];
                i_r++;
            }
        }
    }
