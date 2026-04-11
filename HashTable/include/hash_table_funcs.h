#ifndef HASH_TABLE_FUNCS
#define HASH_TABLE_FUNCS

#include <stdio.h>

#include "list_functions.h"
#include "dump_functions.h"
#include "set_get_functions.h"

enum ReturnStatus
{
    success = 0,
    error = -1,
};

struct HashTable
{
    size_t size;
    size_t (*hash_func)(char* word);
    StructList** table;
};

#endif