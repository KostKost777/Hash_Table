#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/stat.h>

#include "hash_table_funcs.h"
#include "hash_table_dump_funcs.h"
#include "parse_db_from_file.h"

void FillBufferFromFile(struct Buffer* buffer, char* file_name)
{
    assert(file_name);

    FILE* file = fopen(file_name, "a+");
    assert(file);

    buffer->size= GetSizeOfFile(file_name);
    buffer->size++;

    printf("SIZE: %d\n", buffer->size);

    buffer->data = (char*)calloc(buffer->size, sizeof(char));

    size_t read_symbols = fread(buffer->data, sizeof(char), buffer->size, file);
    buffer->data[buffer->size - 1] = '\0';

    if (read_symbols + 1 != buffer->size)
    {
        assert(false);
        free(buffer->data);
    }

    ReplaceSymbolInBuffer(buffer, '\n', '\0');
}

void FillHashTableFromBuffer(struct HashTable* hash_table, struct Buffer* buffer)
{
    assert(hash_table);
    assert(buffer);

    char* word_begin_ptr = buffer->data;
    char* cur_sym_ptr    = buffer->data;

    for (int i = 0; i < buffer->size; ++i, cur_sym_ptr++)
    {
        if (*cur_sym_ptr == '\0')
        {
            AddElemInHashTable(hash_table, word_begin_ptr);
            word_begin_ptr = cur_sym_ptr + 1;
        }
    }
}

void ReplaceSymbolInBuffer(struct Buffer* buffer, char old_sym, char new_sym)
{
    for (int i = 0; i < buffer->size; ++i)
    {
        if (buffer->data[i] == old_sym)
            buffer->data[i] = new_sym;
    }
}

ssize_t GetSizeOfFile(const char* filename)
{
    assert(filename != NULL);
    struct stat file_info = {};

    if (stat(filename, &file_info) == -1) {
        assert(true);
        return -1;
    }
    return file_info.st_size;
}

