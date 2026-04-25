#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <immintrin.h>
#include <sys/stat.h>

#include "hash_table_funcs.h"
#include "hash_table_dump_funcs.h"
#include "parse_db_from_file.h"

void FillBufferFromFile(struct Buffer* buffer, const char* file_name)
{
    assert(file_name);

    FILE* file = fopen(file_name, "a+");
    assert(file);

    ssize_t file_size = GetSizeOfFile(file_name);
    assert(file_size != -1);

    buffer->size = (size_t)file_size; 
    buffer->size++;

    //printf("SIZE: %llu\n", buffer->size);

    buffer->data = (char*)calloc(buffer->size, sizeof(char));

    buffer->data = (char*)aligned_alloc(MAX_LEN, buffer->size + MAX_LEN);
    assert(buffer->data);
    
    memset(buffer->data, 0, buffer->size + MAX_LEN);

    fread(buffer->data, sizeof(char), buffer->size, file);
    buffer->data[buffer->size] = '\0';

    ReplaceSymbolInBuffer(buffer, '\n', '\0');

    fclose(file);
}

void FillHashTableFromBuffer(struct HashTable* hash_table, struct Buffer* buffer)
{
    assert(hash_table);
    assert(buffer);

    char* word_begin_ptr = buffer->data;
    char* cur_sym_ptr    = buffer->data;

    for (size_t i = 0; i < buffer->size; ++i, cur_sym_ptr++)
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
    __m256i old_vec = _mm256_set1_epi8(old_sym);
    __m256i new_vec = _mm256_set1_epi8(new_sym);

    size_t i = 0;

    for(;i + 31 < buffer->size; i += 32)
    {
        __m256i load_vec = _mm256_loadu_si256((__m256i*)(buffer->data + i));
        __m256i mask_vec = _mm256_cmpeq_epi8(load_vec, old_vec);
        __m256i res_vec  = _mm256_blendv_epi8(load_vec, new_vec, mask_vec);
        _mm256_storeu_si256((__m256i*)(buffer->data + i), res_vec);
    }

    for (; i < buffer->size; i++)
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

