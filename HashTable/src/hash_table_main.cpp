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

int main (void)
{
    atexit(CloseLogFile);

    OpenLogFile();

    struct HashTable table = {};

    HashTableCtor(&table, 4001, CRC32_HashFunc);

    struct Buffer buffer = {};

    FillBufferFromFile(&buffer, "database/database.txt");
    FillHashTableFromBuffer(&table, &buffer);

    RunHashTableTestFromFile(&table, "tests/test.txt");

    // FILE* output_file = fopen("../Discription/output.txt", "w+");
    // assert(output_file);

    // WriteHashTableDistribution(&table, output_file);

    //HashTableDump(&table, "");
    HashTableDtor(&table);
    free(buffer.data);
}