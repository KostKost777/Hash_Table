#ifndef PARSE_DB_FROM_FILE
#define PARSE_DB_FROM_FILE

struct Buffer
{
    char*  data;
    size_t size;
};

void FillBufferFromFile(struct Buffer* buffer, char* file_name);

void FillHashTableFromBuffer(struct HashTable* hash_table, 
                             struct Buffer*    buffer);

ssize_t GetSizeOfFile(const char* file_name);

void ReplaceSymbolInBuffer(struct Buffer* buffer, char old_sym, 
                                                  char new_sym);

#endif
