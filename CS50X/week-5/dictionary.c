// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Number of words in dictionary 
int len_dict = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to get position to start search
    int hash_index = hash(word);

    node *current_node = table[hash_index];
    while (current_node != NULL)
    {
        if (strcasecmp(word, current_node->word) == 0)
        {
            return true;
        }

        current_node = current_node->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;  
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file with pathname dictionary in read mode
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return 1;
    }

    char buffer[LENGTH + 1];
    
    while (fscanf(fp, "%s", buffer) != EOF)
    {
        // Allocate memory for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the buffer into the node
        strcpy(n->word, buffer);

        // Hash word and insert into hash table
        int hash_index = hash(n->word);
        n->next = table[hash_index];
        table[hash_index] = n;

        len_dict++;
    }

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return len_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over hash table and free nodes in each linked list
    for (int i = 0; i < N; i++)
    {
        // Assign cursor
        node *n = table[i];
        // Loop through linked list
        while (n != NULL)
        {
            // Make temp equal cursor;
            node *tmp = n;
            // Point cursor to next element
            n = n->next;
            // free temp
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
return false;
}
