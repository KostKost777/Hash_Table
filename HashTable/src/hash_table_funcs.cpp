#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <immintrin.h>
#include <stdarg.h>
#include <errno.h>
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

    hash_table->error_code = 0;

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

    #ifndef BENCHMARK_MODE
    HASH_TABLE_VERIFIER(hash_table);
    #endif

    size_t hash_table_index = hash_table->hash_func(new_word) % hash_table->size;

    if (!IsWordInList(hash_table->table[hash_table_index]->data,
                      hash_table->table[hash_table_index]->num_of_el,
                      new_word))
        InsertAfterTail(hash_table->table[hash_table_index], new_word);
}

void WriteHashTableDistribution(struct HashTable* hash_table, char* hash_func_file_name)
{
    assert(hash_table);
    assert(hash_func_file_name);

    FILE* output_file = fopen(hash_func_file_name, "w");
    assert(output_file);

    for (size_t i = 0; i < hash_table->size; i++)
        fprintf(output_file, "%d\n", hash_table->table[i]->num_of_el);

    fclose(output_file);
}

bool IsWordInList(struct Data* data, int size, char* word)
{
    assert(word);
    assert(data);

    const size_t word_len = strlen(word);

    for (int i = 0; i < size; ++i)
    {
        if (data[i].len == word_len) 
        {
            if (!MyStrCmp(data[i].str, word, word_len))
                return true;
        }
    }
    
    return false;
}

size_t AlwaysZeroHashFunc(char* word)
{
    assert(word);

    return 0;
}

size_t FirstSymbolHashFunc(char* word)
{
    assert(word);

    return (size_t)word[0];
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
        hash += (size_t)word[i];
    
    return hash;
}

size_t ROLHashFunc(char* word) {
    assert(word);
    
    size_t hash = (size_t)word[0];
    
    for (size_t i = 1; word[i] != '\0'; i++) {
        hash = (hash << 1) | (hash >> 63);
        hash ^= (size_t)word[i];
    }
    
    return hash;
}

size_t RORHashFunc(char* word) {
    assert(word);
    
    size_t hash = (size_t)word[0];
    
    for (size_t i = 1; word[i] != '\0'; i++) {
        hash = (hash >> 1) | (hash << 63);
        hash ^= (size_t)word[i];
    }
    
    return hash;
}

size_t DJB2_HashFunc(char* word) 
{
    assert(word);

    size_t hash = 5381;
    for (size_t i = 0; word[i] != '\0'; i++)
        hash = ((hash << 5) + hash) + (size_t)word[i];

    return hash;
}

size_t CRC32_HashFunc(char* word) 
{
    assert(word);
    
    size_t crc = 0xFFFFFFFF;
    
    for (size_t i = 0; word[i] != '\0'; i++) {
        size_t byte = (size_t)word[i];
        crc ^= byte;
        
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    
    return (crc ^ 0xFFFFFFFF);
}

size_t CRC32_HashFunc_SIMD(char* word) 
{
    assert(word);

    unsigned int hash = 0xFFFFFFFF;
    for (size_t i = 0; word[i] != '\0'; i++) 
        hash = _mm_crc32_u8(hash, (uint8_t)word[i]);
    
    return (size_t)hash ^ 0xFFFFFFFF;
}