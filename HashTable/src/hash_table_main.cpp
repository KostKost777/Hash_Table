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

    HashTableCtor(&table, 14999, CRC32_HashFunc_SIMD);

    struct Buffer buffer = {};

    FillBufferFromFile(&buffer, "database/database.txt");

    struct PtrArray ptr_arr = {};

    FillPtrArrayFromBuffer(&buffer, &ptr_arr);

    FillHashTableFromPtrArr(&table, &ptr_arr);

    volatile size_t res = RunHashTableTestFromFile(&table, "tests/test.txt", 100);
    printf("FIND: %d\n", res);
    
    // FILE* output_file = fopen("../Discription/output.txt", "w+");
    // assert(output_file);

    // WriteHashTableDistribution(&table, output_file);

    //HashTableDump(&table, "");

    HashTableDtor(&table);
    BufferDtor(&buffer);
    PtrArrayDtor(&ptr_arr);
}