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

const char* db_file_name    = "database/database.txt";
const char* tests_file_name = "tests/test.txt";

const int NUM_OF_TEST = 100;

int main (void)
{
    atexit(CloseLogFile);

    OpenLogFile();

    // struct HashFunc hash_funcs[] = {    {AlwaysZeroHashFunc,  4001, "AlwaysZeroHashFunc"},
    //                                     {FirstSymbolHashFunc, 4001, "FirstSymbolHashFunc"},
    //                                     {LineLenHashFunc,     4001, "LineLenHashFunc"},
    //                                     {SymbolSumHashFunc,   1009, "SymbolSumHashFunc"},
    //                                     {SymbolSumHashFunc,   4001, "SymbolSumHashFunc"},
    //                                     {ROLHashFunc,   4001, "ROLHashFunc"},
    //                                     {RORHashFunc,  4001,  "RORHashFunc"},
    //                                     {DJB2_HashFunc,       4001, "DJB2_HashFunc"},
    //                                     {CRC32_HashFunc,      4001, "CRC32_HashFunc"},
    //                                 };

    // GetHashFuncsWordDistribution(hash_funcs, 
    //                              sizeof(hash_funcs) / sizeof(hash_funcs[0]),  
    //                              db_file_name);

    struct HashTable table = {};

    HashTableCtor(&table, 14999, CRC32_HashFunc_SIMD);

    struct Buffer buffer = {};

    FillBufferFromFile(&buffer, db_file_name);

    struct PtrArray ptr_arr = {};

    FillPtrArrayFromBuffer(&buffer, &ptr_arr);

    FillHashTableFromPtrArr(&table, &ptr_arr);

    volatile size_t res = RunHashTableTestFromFile(&table, tests_file_name, NUM_OF_TEST);
    printf("FIND: %d\n", res);

    WriteHashTableDistribution(&table, "../Discription/outfile.txt");

    //HashTableDump(&table, "");

    HashTableDtor(&table);
    BufferDtor(&buffer);
    PtrArrayDtor(&ptr_arr);
}