#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "hash_table_funcs.h"

void HashTableCtor(HashTable* hash_table, size_t size,
                  size_t (*hash_func)(char* word))
{
    assert(hash_table);
    assert(hash_func);

    hash_table->size = size;
    hash_table->hash_func = hash_func;

    hash_table->table = (StructList**)calloc(sizeof(StructList*), size);
    assert(hash_table->table);

    for (size_t i = 0; i < size; ++i)
    {
        StructList* list = (StructList*)calloc(sizeof(StructList), 1);
        assert(list);

        ListCtor(list, 1);

        hash_table->table[i] = list;
    }
}

void HashTableDtor(HashTable* hash_table)
{
    assert(hash_table);

    for (size_t i = 0; i < hash_table->size; ++i)
        ListDtor(hash_table->table[i]);

    free(hash_table->table);
}

void AddElemInHashTable(HashTable* hash_table, char* new_word)
{
    assert(hash_table);
    assert(new_word);

    size_t hash = hash_table->hash_func(new_word) % hash_table->size;

    InsertAfterTail(hash_table->table[hash], new_word);

}

size_t AlwaysZeroHashFunc(char* word)
{
    assert(word);
    return 0;
}

size_t FirstSymbolHashFunc(char* word)
{
    assert(word);
    return word[0];
}

size_t LineLenHashFunc(char* word)
{
    assert(word);
    return strlen(word);
}

size_t SymbolhashHashFunc(char* word)
{
    assert(word);
    size_t hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
        hash += word[i];
    
    return hash;
}

size_t LeftShiftHashFunc(char* word)
{
    assert(word);
    size_t hash = word[0];
    for (int i = 0; word[i] != '\0'; i++)
        hash = (hash << 1) ^ word[i];
    
    return hash;
}

size_t RightShiftHashFunc(char* word)
{
    assert(word);
    size_t hash = word[0];
    for (int i = 0; word[i] != '\0'; i++)
        hash = (hash >> 1) ^ word[i];
    
    return hash;
}