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
    size_t hash_table_index      = 0;
    size_t hash_table_next_index = 0;

    uint64_t reverse_table_size = (uint64_t)((((__uint128_t)1 << 64)) / hash_table->size + 1);

    for (int count = 0; count < iter; ++count)
    {
        size_t i = 0;
        for(; i < ptr_arr.size - 1; ++i)
        {
            size_t hash_value_1 = hash_table->hash_func(ptr_arr.data[i]);
            size_t hash_value_2 = hash_table->hash_func(ptr_arr.data[i + 1]);

            uint64_t quotient_1 = 0;
            uint64_t quotient_2 = 0;

            __asm__ (
                ".intel_syntax noprefix\n"

                "mulx rbx, rcx, %[hash_value_2]\n" 
                "mulx rax, rcx, %[hash_value_1]\n" 
                
                ".att_syntax prefix\n"

                : "=a" (quotient_1),
                  "=b" (quotient_2)

                : [hash_value_1] "r" (hash_value_1),
                  [hash_value_2] "r" (hash_value_2),
                                 "d" (reverse_table_size)

                : "rcx", "cc"
            );

            hash_table_index      = hash_value_1 - quotient_1 * hash_table->size;
            hash_table_next_index = hash_value_2 - quotient_2 * hash_table->size;

             __asm__ __volatile__ (
                "prefetcht0 %0\n\t"
                "prefetcht0 %1\n\t"
                : 
                : "m" (hash_table->table[hash_table_next_index]->data),
                  "m" (hash_table->table[hash_table_next_index]->num_of_el)
            );


            find_words += IsWordInList(hash_table->table[hash_table_index]->data, 
                                       hash_table->table[hash_table_index]->num_of_el,
                                       ptr_arr.data[i]);
        }


        hash_table_index = hash_table->hash_func(ptr_arr.data[i]) % hash_table->size;

        find_words += IsWordInList(hash_table->table[hash_table_index]->data, 
                                    hash_table->table[hash_table_index]->num_of_el,
                                    ptr_arr.data[i]);
        
    }
    
    fclose(test_file);

    BufferDtor(&buffer);
    PtrArrayDtor(&ptr_arr);

    return find_words;
}
