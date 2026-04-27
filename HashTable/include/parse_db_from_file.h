#ifndef PARSE_DB_FROM_FILE
#define PARSE_DB_FROM_FILE

struct Buffer
{
    char*  data;
    size_t size;
};

struct PtrArray
{
    char** data;
    size_t size;
};

void FillBufferFromFile(struct Buffer* buffer, const char* file_name);

void FillHashTableFromPtrArr(struct HashTable* hash_table, struct PtrArray* ptr_arr);

ssize_t GetSizeOfFile(const char* file_name);

void ReplaceSymbolInBuffer(struct Buffer* buffer, char old_sym, 
                                                  char new_sym);

size_t CountWordInBuffer(struct Buffer* buffer);

void FillPtrArrayFromBuffer(struct Buffer* buffer, struct PtrArray* ptr_arr);

void BufferDtor(struct Buffer* buffer);

void PtrArrayDtor(struct PtrArray* ptr_arr);



#endif
