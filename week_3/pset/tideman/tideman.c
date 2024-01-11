#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// Mine
void print_preferences(void);
void print_pairs(void);
bool isCycle(int i);
bool isCycle_util(int i, int j);
void print_locked(void);
typedef struct
{
    int items[MAX * (MAX - 1) / 2];
    int top;
} stack;

int main(int argc, string argv[])
{
    bool locked_local[MAX][MAX];
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check name if valid candidate
    bool checks_out = false;
    for (int candidate_i = 0; candidate_i < candidate_count; candidate_i++)
    {
        if (strcmp(name, candidates[candidate_i]) == 0)
        {
            checks_out = true;
            // store candidate "i"
            ranks[rank] = candidate_i;
        }
    }
    if (!checks_out)
    {
        return false;
    }
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // start from 0 (rank 1)
    for (int i = 0; i < candidate_count; i++)
    {
        // compare to everyone else
        for (int j = i + 1; j < candidate_count; j++)
        {
            // use ranks[] as coordinates
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    // DEBUG
    // print_preferences();

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop over preferences[i][j]
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if preferred (people voted for them higher than someone else)
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // update pair_count
                pair_count++;
            }
        }
    }

    // DEBUG

    // print_pairs();
    // printf("\n");

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    // loop through pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // if the next pair's number of votes is greater than current pair, swap
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }

    // DEBUG
    // printf("Sorted ");
    // print_pairs();
    // printf("\n");

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Implement Depth-First Search to search for cycles
    // Using Stacks implementation of DFS
    // stacks implemented using struct

    // go through sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        // lock a pair if it doesn't form a cycle
        if (!isCycle(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            // DEBUG
            // printf("Locked: %i %i\n", pairs[i].winner, pairs[i].loser);
        }
    }

    // DEBUG
    // print_locked();
    // printf("\n");

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // find the source node by adding up all the locks for each candidate
    int lock_tally[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        lock_tally[i] = 0;
    }
    // Loop through all the locks
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // tally the locks for each candidate only
            lock_tally[i] += (int) locked[j][i];
        }
    }
    // Winner has 0 locks
    for (int i = 0; i < candidate_count; i++)
    {
        if (lock_tally[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

///////////////////////////////////////////////////////////////////

void print_preferences(void)
{
    printf("Preferences:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

void print_pairs(void)
{
    printf("Pairs:\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i %i", pairs[i].winner, pairs[i].loser);
        printf("\n");
    }
    return;
}

void print_locked(void)
{
    printf("Locked:\n");
    bool lock = false;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            lock = locked[i][j];
            printf("%i ", lock);
        }
        printf("\n");
    }
}

bool isCycle(int i)
{
    // Check if loser points to anyone else
    for (int j = 0; j < candidate_count; j++)
    {
        if (pairs[j].winner == pairs[i].loser)
        {
            // utility function to recursively check all edges of current node
            if (isCycle_util(i, j))
            {
                return true;
            }
        }
    }
    return false;
}

bool isCycle_util(int i, int j)
{
    // check if current node has no arrows pointing outwards
    if (locked[pairs[j].winner][pairs[j].loser] == false)
    {
        // if not, it's not pointing to anything
        return false; // go back
    }
    // if pointing, recursively check what it's pointing at
    for (int k = 0; k < candidate_count; k++)
    {
        if (pairs[k].winner == pairs[j].loser)
        {
            // check if it's pointing at the starting node
            if (pairs[k].loser == pairs[i].winner)
            {
                return true; // it's a cycle
            }
            // repeat
            if (isCycle_util(i, k))
            {
                return true; // it's a cycle
            }
        }
    }
    return false; // not a cycle
}
