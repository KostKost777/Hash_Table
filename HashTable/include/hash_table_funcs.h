#ifndef HASH_TABLE_FUNCS
#define HASH_TABLE_FUNCS

#include <stdio.h>

#include "list_functions.h"
#include "dump_functions.h"
#include "set_get_functions.h"
#include <stdint.h>

const size_t MAX_LEN = 32;

struct HashTable
{
    size_t size;
    size_t (*hash_func)(char* word);
    StructList** table;
    int error_code;
};

void HashTableCtor(HashTable* hash_table, size_t size, 
                   size_t (*hash_func)(char* word));

void HashTableDtor(HashTable* hash_table);

void WriteHashTableDistribution(struct HashTable* hash_table, char* hash_func_file_name);

void AddElemInHashTable(HashTable* hash_table, char* new_word);

bool IsWordInList(struct Data* data, int size, char* word);

size_t AlwaysZeroHashFunc(char* word);

size_t FirstSymbolHashFunc(char* word);

size_t LineLenHashFunc(char* word);

size_t SymbolSumHashFunc(char* word);

size_t ROLHashFunc(char* word);

size_t RORHashFunc(char* word);

size_t CRC32_HashFunc(char* word);

size_t CRC32_HashFunc_SIMD(char* word);

size_t DJB2_HashFunc(char* word);

extern "C" {
    int MyStrCmp(const char* str1, const char* str2, uint8_t size);
}

#endif