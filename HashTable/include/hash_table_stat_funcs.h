#ifndef HASH_TABLE_STAT_FUNCS
#define HASH_TABLE_STAT_FUNCS

#include <stdio.h>

struct HashFunc
{
    size_t (*hash_func)(char* word);
    size_t table_size;
    const char* name;
};

void GetHashFuncsWordDistribution(struct HashFunc* hash_funcs_array, 
                                  size_t num_of_funcs,
                                  const char* db_file_name);
                                  
char* GetNewHashFuncFileName(struct HashFunc hash_func);
#endif