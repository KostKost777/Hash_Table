#ifndef HASH_TABLE_DUMP_FUNCS
#define HASH_TABLE_DUMP_FUNCS

#include "hash_table_funcs.h"

const int MAX_SIZE = 10e4;

enum ErrCodes
{
    BAD_SIZE = 1,
    BAD_HASH_FUNC = 2,
    BAD_LIST_ARR = 4
};

void PrintHashTableError(struct HashTable* hash_table);

enum ReturnStatus HashTableDump(HashTable* hash_table, const char* message, ...);

enum ReturnStatus HashTableVerifier(HashTable* hash_table);

#define HASH_TABLE_VERIFIER(hash_table)  \
        if (HashTableVerifier(hash_table) == error) \
            HashTableDump(hash_table, "\n<h3> FIND ERROR </h3>"); \

#endif