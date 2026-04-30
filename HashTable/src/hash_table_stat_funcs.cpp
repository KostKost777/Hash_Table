#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "list_functions.h"
#include "dump_functions.h"
#include "set_get_functions.h"

#include "hash_table_funcs.h"
#include "hash_table_dump_funcs.h"
#include "hash_table_test_funcs.h"
#include "parse_db_from_file.h"
#include "hash_table_stat_funcs.h"

void GetHashFuncsWordDistribution(struct HashFunc* hash_funcs_array, 
                                  size_t num_of_funcs,
                                  const char* db_file_name)
{
    assert(hash_funcs_array);
    assert(db_file_name);

    struct Buffer buffer = {};
    FillBufferFromFile(&buffer, db_file_name);

    struct PtrArray ptr_arr = {};
    FillPtrArrayFromBuffer(&buffer, &ptr_arr);

    for (size_t i = 0; i < num_of_funcs; ++i)
    {
        struct HashTable table = {};
        HashTableCtor(&table, hash_funcs_array[i].table_size,  hash_funcs_array[i].hash_func);

        printf("%s\n", hash_funcs_array[i].name);

        FillHashTableFromPtrArr(&table, &ptr_arr);

        char* hash_func_file_name = GetNewHashFuncFileName(hash_funcs_array[i]);

        WriteHashTableDistribution(&table, hash_func_file_name);

        HashTableDtor(&table);

        free(hash_func_file_name);
    }

    BufferDtor(&buffer);
    PtrArrayDtor(&ptr_arr);
}

char* GetNewHashFuncFileName(struct HashFunc hash_func)
{
    char str_file_name[100] = "";

    snprintf(str_file_name, sizeof(str_file_name),
             "../Discription/1_task/func_name:_%s_table_size:_%llu.txt", hash_func.name, 
                                                                hash_func.table_size);

    return strdup(str_file_name);
}