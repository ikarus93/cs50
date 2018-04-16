// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

node *hashtable[26];
unsigned int dic_size = 0;

//Prototypes
int hash(const char *word);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int idx = hash(word);
    node *cursor = hashtable[idx];
    bool found = false;

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            found = true;
            break;
        }
        cursor = cursor->next;
    }

    return found;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic = fopen(dictionary, "r");
    char word[LENGTH + 1];


    //Initializing heads for hash table
    for (int i = 0; i < 26; i++)
    {
        node *head = malloc(sizeof(node));
        head->next = NULL;
        hashtable[i] = head;
    }

    //Scan over file
    while (fscanf(dic, "%s", word) != EOF)
    {
        //Allocate memory for new linked list item
        node *new_node = malloc(sizeof(node));
        //check if we didnt run out of memory
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        //copy word into new node
        strcpy(new_node->word, word);

        //hash word
        int idx = hash(word);

        //insert into hashtable
        node *head = hashtable[idx];
        //If the linked list already contains entries
        if (head->next)
        {
            new_node->next = head->next;
            head->next = new_node;
        }
        else
        {
            new_node->next = NULL;
            head->next = new_node;
        }
        dic_size++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dic_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < 26; i++)
    {
        node *cursor = hashtable[i];

        if(cursor->next != NULL)
        {
            while (cursor->next != NULL)
            {
                node *temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
        }
        //Free all hashtable heads that dont containt children
        else
        {
            free(cursor);
        }

    }
    return true;
}

int hash(const char *word) {
	char x = word[0];
	int idx = isupper(x) ? x - 65 : x - 97;
	return idx;
}
