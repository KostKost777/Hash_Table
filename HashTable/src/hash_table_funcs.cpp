#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <immintrin.h>
#include <stdint.h>

#include "list_functions.h"
#include "dump_functions.h"
#include "set_get_functions.h"

#include "hash_table_funcs.h"
#include "hash_table_dump_funcs.h"

void HashTableCtor(HashTable* hash_table, size_t size,
                  size_t (*hash_func)(char* word))
{
    assert(hash_table);
    assert(hash_func);

    hash_table->size      = size;
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
    {
        ListDtor(hash_table->table[i]);
        free(hash_table->table[i]);
    }
        

    free(hash_table->table);
}

void AddElemInHashTable(HashTable* hash_table, char* new_word)
{
    assert(hash_table);
    assert(new_word);

    size_t hash = hash_table->hash_func(new_word) % hash_table->size;

    if (!IsWordExistInList(hash_table->table[hash], new_word))
        InsertAfterTail(hash_table->table[hash], new_word);
}

bool IsWordExistInList(struct StructList* list, char* word)
{
    assert(list);
    assert(word);

    for (size_t i = 1; i <= list->num_of_el; ++i)
        if (!strncmp(list->data[i], word, MAX_LEN))
            return true;
    
    return false;
}

void WriteHashTableDistribution(struct HashTable* hash_table, FILE* output_file)
{
    assert(hash_table);

    for (size_t i = 0; i < hash_table->size; i++)
        fprintf(output_file, "%d\n", hash_table->table[i]->num_of_el);
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

size_t SymbolSumHashFunc(char* word)
{
    assert(word);
    size_t hash = 0;
    for (size_t i = 0; word[i] != '\0'; i++)
        hash += word[i];
    
    return hash;
}

size_t LeftShiftHashFunc(char* word)
{
    assert(word);
    size_t hash = word[0];
    for (size_t i = 0; word[i] != '\0'; i++)
        hash = (hash << 1) ^ word[i];
    
    return hash;
}

size_t RightShiftHashFunc(char* word)
{
    assert(word);
    size_t hash = word[0];
    for (size_t i = 0; word[i] != '\0'; i++)
        hash = (hash >> 1) ^ word[i];
    
    return hash;
}

size_t CRC32_HashFunc(char* word) 
{
    size_t hash = 0xFFFFFFFF;
    
    for (size_t i = 0; word[i] != '\0'; i++) 
        hash = _mm_crc32_u8(hash, (uint8_t)word[i]);
    
    return hash ^ 0xFFFFFFFF;
}