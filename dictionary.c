// Implements a dictionary's functionality
#define _XOPEN_SOURCE 500
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>



typedef struct ht_item{
    char* value;
} ht_item;

// Define a structure containing the size(number of items), count and a pointer to a pointer containing the ht_item struct.
typedef struct hash_table{
    int size;
    int alphabetSize;
    ht_item** items;
} hash_table;

static int hash (const char* value, int size, int alphabetSize);
void ht_insert(const char* value);
static int ht_get_hash (const char* value, int size, int attempt);

hash_table* ht_new();

FILE* dict;
int words;
hash_table* ht;

// Instantiates(creates) a malloced struct, copies the value passed to the function into the created variable and returns the struct.
ht_item* ht_new_item(const char* value){
    ht_item* item = malloc(sizeof(ht_item));
    item->value = strdup(value);
    return item;
}

// Instantiates a new hash table and sets the alphabet size to 127, this is due to using ASCII and only allowing alphanumeric characters,
// this is required to be a prime number, the closest of which is 127. It then sets array size, I'm pulling this from the total words in the
// dictionary, it then returns the table to the calling function.
hash_table* ht_new(){
    hash_table* i = malloc(sizeof(hash_table));
    i->size = 214667;
    i->alphabetSize = 151;
    i->items = calloc(i->size, sizeof(ht_item));
    return i;
}


// Takes the hash table and the value to be placed in the table, It runs the value through the hashing function to create an index
// between 0 - 143091 and stores the value in the index variable, It then stores the value at that location in the table.
void ht_insert(const char* value){
    int index = ht_get_hash(value, ht->size, 0);
    ht_item* item = ht_new_item(value);
    int i = 1;
    while(ht->items[index] != NULL){
        index = ht_get_hash(value, ht->size, i);
        i++;
    }
    ht->items[index] =  item;
}

// Generate a hash based on the string passed in and returns that value to the calling function.
static int hash (const char* value, int alphabetSize, int size){
    long hash = 0;
    int len_s = strlen(value);
    for (int i = 0; i < len_s; i++){
        hash += (long)pow(alphabetSize, len_s - (i+1)) * value[i];
        hash = hash % size;
    }
    //fprintf(stdout, "%i\n", (int) hash);
    return (int) hash;
}

static int ht_get_hash (const char* value, int size, int attempt){
    int prime_1 = 53, prime_2= 57;
    const int hash_a = hash(value, prime_1, size);
    const int hash_b = hash(value, prime_2, size);
    return (hash_a + (attempt * (hash_b + 1))) % size;
}

// Takes the table, value, size and alphabetsize, Runs the value through the hashing function to create an index to searxch atl, It will
// return value not found if the returned index is NULL and the value itself at that index if it is not NULL.
bool ht_search(const char* value, int size){
    int index = ht_get_hash(value, size, 0);
    int i = 1;
    while (ht->items[index] != NULL){
        if (strcmp(ht->items[index]->value, value) == 0){
            return true;
        }
        index = ht_get_hash(value, size, i);
        i++;
    }
    return false;
}

bool check(const char *word)
{

    //Get length of 'word'.
    int wordLength = strlen(word);

    //Create variable to store 'word' in lowercase.
    char wordLower[wordLength + 1];

    //Convert word to lowercase.
    for(int i = 0; i <= wordLength; i++){
        wordLower[i] = tolower(word[i]);
    }
    return ht_search(wordLower, ht->size);
};

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char dictWord[LENGTH + 1];
    ht = ht_new();
    if ((dict = fopen(dictionary, "r")) == NULL){
        return false;
    }

    for(int i = 0; i <= 143091; i++){
        fscanf(dict, "%s", dictWord);
        ht_insert(dictWord);
    }

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    fseek(dict, 0, SEEK_SET);
    int c;
    while((c = fgetc(dict)) && !feof(dict)){
        if (c == '\n'){ words++;};
    }
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    free(ht->items);
    free(ht);
    if (fclose(dict) == 0){
        return true;
    }
    return false;
}
