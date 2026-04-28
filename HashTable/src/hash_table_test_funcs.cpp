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

size_t RunHashTableTestFromFile(struct HashTable* hash_table, const char* test_file_name, int iter)
{
    assert(hash_table);
    assert(test_file_name);

    FILE* test_file = fopen(test_file_name, "r");
    assert(test_file);

    struct Buffer buffer = {};

    FillBufferFromFile(&buffer, test_file_name);

    struct PtrArray ptr_arr = {};

    FillPtrArrayFromBuffer(&buffer, &ptr_arr);

    size_t find_words = 0;
    size_t hash_table_index = 0;

    uint64_t reverse_table_size = (uint64_t)((((__uint128_t)1 << 64)) / hash_table->size + 1);

    for (int count = 0; count < iter; ++count)
    {
        for(size_t i = 0; i < ptr_arr.size; ++i)
        {
            size_t hash_value = hash_table->hash_func(ptr_arr.data[i]);
            uint64_t quotient = 0;

            __asm__ (
                ".intel_syntax noprefix\n"
                "mulx %[hash_value], rcx, rax\n" 
                ".att_syntax prefix\n"
                : [quotient] "=a" (quotient) 
                : [hash_value] "r" (hash_value),
                "d" (reverse_table_size)
                : "rcx", "cc"
            );

            hash_table_index = hash_value - quotient * hash_table->size;

            find_words += IsWordInList(hash_table->table[hash_table_index], 
                                       ptr_arr.data[i]);
        }
    }
    
    fclose(test_file);

    BufferDtor(&buffer);
    PtrArrayDtor(&ptr_arr);

    return find_words;
}
