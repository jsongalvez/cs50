/**
 * cs50x
 * March 24-25, 2023
 * Galvez, Jayson S.
 * plurality.c
 *
 * 1) list candidates and number of voters
 * 2) vote
 * 3) prints candidates with highest vote
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Linear search for candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Count vote and return true if found
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // return false if not found
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // using two-step linear search
    // step one: find max value
    int start = 0;
    int max_value = candidates[start].votes;
    for (int i = start + 1; i < candidate_count; i++)
    {
        if (max_value <= candidates[i].votes)
        {
            max_value = candidates[i].votes;
        }
    }
    // step two: use max value to find candidates with highest votes
    for (int i = start; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_value)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
