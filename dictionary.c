// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void recursiveUnload(node *ptr);

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Number of words in the dictionary
int numberWords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashIndex = hash(word);

    node *pointer = table[hashIndex];

    while (pointer != NULL)
    {
        if(strcasecmp(word, pointer->word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hash = 0;
    int decimalHouse = 1;
    for (int i = 0; i <= strlen(word); i++)
    {
        hash += tolower(word[i]) * decimalHouse;
        decimalHouse *= 10;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
        FILE *DICTIONARY = fopen(dictionary, "r");
        if (DICTIONARY == NULL)
        {
            unload();
            return false;
        }

        node *pointer = malloc(sizeof(node));
        if (pointer == NULL)
        {
            fclose(DICTIONARY);
            return false;
        }

        char c;

        int wordIndex = 0;

        while (fread(&c, sizeof(char), 1, DICTIONARY))
        {
            if (c =='\n')
            {
                int hashIndex = hash(pointer->word);
                pointer->next = table[hashIndex];
                table[hashIndex] = pointer;
                pointer = malloc(sizeof(node));
                if (pointer == NULL)
                {
                    fclose(DICTIONARY);
                    unload();
                    return false;
                }
                wordIndex = 0;
                numberWords++;
            }
            else
            {
                pointer->word[wordIndex] = c;
                wordIndex++;
            }
        }
        fclose(DICTIONARY);
        free(pointer);
        return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numberWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *pointer;

    for (int index = 0; index < N; index++)
    {
        pointer = table[index];
        recursiveUnload(pointer);
    }
    return true;
}

void recursiveUnload(node *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    recursiveUnload(ptr->next);

    free(ptr);

    return;
}
