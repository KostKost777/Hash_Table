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
#include "parse_db_from_file.h"

int main (void)
{
    atexit(CloseLogFile);

    OpenLogFile();

    struct HashTable table = {};

    HashTableCtor(&table, 7, AlwaysZeroHashFunc);

    struct Buffer buffer = {};

    FillBufferFromFile(&buffer, "database/database.txt");

    FillHashTableFromBuffer(&table, &buffer);

    printf("\n%s\n", buffer);

    // AddElemInHashTable(&table, "HELLO");
    // AddElemInHashTable(&table, "Bebra");

    HashTableDump(&table, "");
    HashTableDtor(&table);

    free(buffer.data);
}