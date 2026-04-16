#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "hash_table_dump_funcs.h"
#include "hash_table_funcs.h"

void HashTableDump(HashTable* hash_table, const char* message, ...)
{
    assert(hash_table);
    assert(message);

    va_list args = {};
    va_start(args, message);

    vfprintf(log_file, message, args);
    fflush(log_file);

    va_end(args);

    for (size_t i = 0; i < hash_table->size; ++i)
        ListDump(hash_table->table[i], "<h2>Индекс списка: %d<h2>", i);
    
}