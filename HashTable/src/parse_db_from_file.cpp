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

    FILE* file = fopen(file_name, "r");
    assert(file);

    ssize_t file_size = GetSizeOfFile(file_name);
    assert(file_size != -1);

    buffer->size = (size_t)file_size; 
    buffer->size++;

    //printf("SIZE: %llu\n", buffer->size);

    buffer->data = (char*)calloc(buffer->size + 1, sizeof(char));

    size_t read_symbols = fread(buffer->data, sizeof(char), buffer->size, file);
    buffer->data[buffer->size - 1] = '\0';

    if (read_symbols + 1 != buffer->size)
    {
        assert(false);
        free(buffer->data);
    }

    ReplaceSymbolInBuffer(buffer, '\n', '\0');
}

void FillPtrArrayFromBuffer(struct Buffer* buffer, struct PtrArray* ptr_arr)
{
    assert(buffer);
    assert(ptr_arr);

    ptr_arr->size = CountWordInBuffer(buffer);

    //printf("PTR_ARR_SIZE: %llu\n", ptr_arr->size);

    ptr_arr->data = (char**)calloc(ptr_arr->size, sizeof(char*));

    char* word_begin_ptr = buffer->data;
    size_t ptr_arr_iter = 0;

    for (size_t buffer_iter = 0; buffer_iter < buffer->size; ++buffer_iter)
    {
        if (buffer->data[buffer_iter] == '\0')
        {
            ptr_arr->data[ptr_arr_iter] = word_begin_ptr;
            word_begin_ptr = buffer->data + buffer_iter + 1;
            ptr_arr_iter++;
        }
    }
}

size_t CountWordInBuffer(struct Buffer* buffer)
{
    assert(buffer);

    size_t num_of_words = 0;

    for (size_t i = 0; i < buffer->size; ++i)
        if (buffer->data[i] == '\0') 
            num_of_words++;

    return num_of_words;
}

void FillHashTableFromPtrArr(struct HashTable* hash_table, struct PtrArray* ptr_arr)
{
    assert(hash_table);
    assert(ptr_arr);

    for (size_t i = 0; i < ptr_arr->size; ++i)
        AddElemInHashTable(hash_table, ptr_arr->data[i]);
    
}

void ReplaceSymbolInBuffer(struct Buffer* buffer, char old_sym, char new_sym)
{
    for (size_t i = 0; i < buffer->size; ++i)
    {
        if (buffer->data[i] == old_sym)
            buffer->data[i] = new_sym;
    }
}

// void ReplaceSymbolInBuffer(struct Buffer* buffer, char old_sym, char new_sym)
// {
//     __m256i old_vec = _mm256_set1_epi8(old_sym);
//     __m256i new_vec = _mm256_set1_epi8(new_sym);

//     size_t i = 0;

//     for(;i + 31 < buffer->size; i += 32)
//     {
//         __m256i load_vec = _mm256_loadu_si256((__m256i*)(buffer->data + i));
//         __m256i mask_vec = _mm256_cmpeq_epi8(load_vec, old_vec);
//         __m256i res_vec  = _mm256_blendv_epi8(load_vec, new_vec, mask_vec);
//         _mm256_storeu_si256((__m256i*)(buffer->data + i), res_vec);
//     }

//     for (; i < buffer->size; i++)
//     {
//         if (buffer->data[i] == old_sym)
//             buffer->data[i] = new_sym;
//     }
// }

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

void PtrArrayDtor(struct PtrArray* ptr_arr)
{
    assert(ptr_arr);

    free(ptr_arr->data);
    ptr_arr->size = 0;
}

void BufferDtor(struct Buffer* buffer)
{
    assert(buffer);

    free(buffer->data);
    buffer->size = 0;
}

