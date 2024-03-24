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
// *added* recursion loop for finding if there are any cycles
bool cycle(int winner,int loser);

int main(int argc, string argv[])
{
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    //
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count-1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    //
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int margin;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            margin = preferences[i][j] - preferences[j][i];
            if (margin > 0)
            {
                pairs[pair_count].winner= i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (margin < 0)
            {
                pairs[pair_count].winner= j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    //
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for(;;)
    {
        int swapped = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            for (int j = i + 1; j < pair_count; j++)
            {
                if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
                {
                    pair tmp = pairs [i];
                    pairs[i] = pairs [j];
                    pairs[j] = tmp;
                    swapped++;
                }
            }

        }
            if (swapped == 0)
            {
             break;
            }
    }
    //
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int a = 0; a < pair_count; a++)
    {
        if (!cycle(pairs[a].winner,pairs[a].loser))
        {
            locked[pairs[a].winner][pairs[a].loser] = true;
        }
    }
    //
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool won = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                won = false;
                break;
            }
            if (won == true)
            {
                printf("%s\n", candidates[i]);
            }
        }

    }
    //
    return;
}
// *added* recursive function that finds cycle by checking if the loser of a locked pair eventually 'wins' against the winner of the pair being checked
bool cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[loser][j])
        {
            if (cycle(winner,j))
            {
                return true;
            }
        }
    }
    return false;
}
