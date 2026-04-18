#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "hash_table_dump_funcs.h"
#include "hash_table_funcs.h"

enum ReturnStatus HashTableVerifier(HashTable* hash_table)
{
    assert(hash_table);

    if (hash_table->size > MAX_SIZE || hash_table->size == 0)
    {
        hash_table->error_code |= BAD_SIZE;
        return error;
    }

    if (hash_table->hash_func == NULL)
    {
        hash_table->error_code |= BAD_HASH_FUNC;
        return error;
    }

    if (hash_table->table == NULL)
    {
        hash_table->error_code |= BAD_LIST_ARR;
        return error;
    }

    for (size_t i = 0; i < hash_table->size; ++i)   
        if (ListVerifier(hash_table->table[i]) == error)
            return error;
        
    return success;
}

void PrintHashTableError(struct HashTable* hash_table)
{
    assert(hash_table);

    if (hash_table->error_code & BAD_SIZE)
        fprintf(log_file, "BAD_SIZE - [%d]\n", BAD_SIZE);

    if (hash_table->error_code & BAD_HASH_FUNC)
        fprintf(log_file, "BAD_HASH_FUNC - [%d]\n", BAD_HASH_FUNC);

    if (hash_table->error_code & BAD_LIST_ARR)
        fprintf(log_file, "BAD_LIST_ARR - [%d]\n", BAD_LIST_ARR);
}

enum ReturnStatus HashTableDump(HashTable* hash_table, const char* message, ...)
{
    assert(hash_table);
    assert(message);

    va_list args = {};
    va_start(args, message);

    vfprintf(log_file, message, args);
    fflush(log_file);

    va_end(args);

    for (size_t i = 0; i < hash_table->size; ++i)
        if (ListDump(hash_table->table[i], "<h2>Индекс списка: %d<h2>", i) == error)
            return error;
}