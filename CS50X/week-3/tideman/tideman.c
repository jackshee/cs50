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
}
pair;

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
bool no_path(bool visited[], int src, int dest);
void lock_pairs(void);
void print_winner(void);

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

        printf("\n");

        record_preferences(ranks);

        /* for (int i = 0; i < candidate_count; i++) */
        /* { */
        /*     for (int j=0; j < candidate_count; j++) */
        /*     { */
        /*         printf("%d ", preferences[i][j]); */
        /*     } */    
        /*     printf("\n"); */
        /* } */
        
    }

    add_pairs();
    
    /* for (int i = 0; i < pair_count; i++) */
    /* { */
    /*     printf("(%d,%d) ", pairs[i].winner, pairs[i].loser); */
        
    /* } */
    /* printf("\n"); */
    sort_pairs();

    /* for (int i = 0; i < pair_count; i++) */
    /* { */
    /*     printf("(%d,%d) ", pairs[i].winner, pairs[i].loser); */
        
    /* } */
    /* printf("\n"); */

    lock_pairs();
    /* for (int i = 0; i < candidate_count; i++) */
    /* { */
    /*     for (int j = 0; j < candidate_count; j++) */
    /*     { */
    /*         printf("%d ", locked[i][j]); */
            
    /*     } */
    /*     printf("\n"); */
        
    /* } */
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }    
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; 
        }        
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair new_pair = {i, j};
                pairs[pair_count] = new_pair;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pair new_pair = {j, i};
                pairs[pair_count] = new_pair;
            }
            else{
                continue;
            }
            pair_count++; 
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort
    int swap_counter = -1;

    do
    {
        swap_counter = 0;

        // Look at each adjacent pair
        for (int i = 0; i < pair_count; i++)
        {
            for (int j = i + 1; j < pair_count - 1; j++)
            {
                if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
                {
                    // Swap pairs
                    pair tmp = pairs[i];
                    pairs[i] = pairs[j];
                    pairs[j] = tmp;
                    
                    swap_counter++;
                }
            }
            
        }
    } while (swap_counter != 0);
    return;
}

// Use Depth First Search to find a path from src, dest
bool no_path(bool visited[], int src, int dest)
{
    if (src == dest)
    {
        return false;    
    }

    visited[src] = true;

    for (int adj = 0; adj < candidate_count; adj++)
    {
        if (locked[src][adj] && !visited[adj])
        {
            if (adj == dest)
            {
                return false;    
            }

            if (!no_path(visited, adj, dest))
            {
                return false;
            }
        }
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Check if adding edge creates cycle
        // If an edge (src, dest) is added, a cycle is created if there already exists a path from dest to src

        // Use Depth First Search
        bool visited[candidate_count];
        for (int i = 0; i < candidate_count; i++)
        {
            visited[i] = false;
        }

        if (no_path(visited, pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        bool found_incoming_edge = false;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                found_incoming_edge = true;
                break;                
            }
            
        }

        if (found_incoming_edge)
        {
            continue;
        }
        else
        {
            printf("%s\n", candidates[j]);
            return;
        }
    }
    return;
}
