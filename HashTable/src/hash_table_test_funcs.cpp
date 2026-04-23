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

    char word_buffer[MAX_LEN] = {};

    while (fscanf(test_file, "%31s", word_buffer) == 1)
        IsWordInHashTable(hash_table, word_buffer);
    
    //printf("FIND WORDS: %d\n", find_words);

    fclose(test_file);
}
