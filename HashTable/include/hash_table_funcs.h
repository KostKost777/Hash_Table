#ifndef HASH_TABLE_FUNCS
#define HASH_TABLE_FUNCS

#include <stdio.h>

#include "list_functions.h"
#include "dump_functions.h"
#include "set_get_functions.h"

const size_t MAX_LEN = 32;

struct HashTable
{
    int error_code;
    size_t size;
    size_t (*hash_func)(char* word);
    StructList** table;
};

void HashTableCtor(HashTable* hash_table, size_t size, 
                   size_t (*hash_func)(char* word));

void HashTableDtor(HashTable* hash_table);

bool IsWordExistInList(struct StructList* list, char* word);

void WriteHashTableDistribution(struct HashTable* hash_table, FILE* output_file);

void AddElemInHashTable(HashTable* hash_table, char* new_word);

bool IsWordInHashTable(struct HashTable* hash_table, char* word);

size_t AlwaysZeroHashFunc(char* word);

size_t FirstSymbolHashFunc(char* word);

size_t LineLenHashFunc(char* word);

size_t SymbolSumHashFunc(char* word);

size_t LeftShiftHashFunc(char* word);

size_t RightShiftHashFunc(char* word);

size_t CRC32_HashFunc(char* word);

size_t CRC32_HashFunc_SIMD(char* word);

size_t DJB2_HashFunc(char* word);

#endif