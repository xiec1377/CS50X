// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h> // fix??
#include <stdlib.h> // fix?
#include <string.h> // fix???
#include <strings.h> //strcompcse
#include <ctype.h> // fix?

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z'; //change laterrrrrrrrrrrrrrrrrrrrrrrrrrrr
int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int index = hash(word); //change
    if (table[index] == NULL)
    {
        return false;
    }
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// Source:https://www.youtube.com/watch?v=HsnjdbHMZO8
unsigned int hash(const char *word)
{
    // TO DO
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if(isalpha(word[i]))
        {
            sum += tolower(word[i]);
        }
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1]; // delete ???????
    int index = hash(word);

    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        strcpy(new_node->word, word);
        if (table[index] == NULL)
        {
            table[index] = new_node;
            new_node->next = NULL;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
        counter ++; // change????
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (counter > 0)
    {
        return counter;
    }
    else
    {
        return 1; // delete?
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor->next != '\0')
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return false;

}
