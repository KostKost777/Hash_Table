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

void RunHashTableTestFromFile(struct HashTable* hash_table, const char* test_file_name)
{
    assert(hash_table);
    assert(test_file_name);

    FILE* test_file = fopen(test_file_name, "r+");
    assert(test_file);

    struct Buffer buffer = {};

    FillBufferFromFile(&buffer, test_file_name);

    char* word_begin_ptr = buffer.data;

    for(size_t i = 0; i < buffer.size; ++i)
    {
        if (buffer.data[i] == '\0')
        {
            //printf("%s - %llu \n", word_begin_ptr, i);
            IsWordInHashTable(hash_table, word_begin_ptr);
            word_begin_ptr = buffer.data + i + 1;
        }
    }
    
    //printf("FIND WORDS: %d\n", find_words);

    fclose(test_file);
}
