#ifndef LIST_FUNC
#define LIST_FUNC

extern const char* PZN;

const int MAX_CAPACITY = 1E6;

extern const char* CANARY;

enum ReturnStatus
{
    success = 0,
    error = -1,
    fatal_error = -2,
};

struct StructList
{
    const char** data;
    int* next;
    int* prev;
    int free;
    int capacity;
    int num_of_el;
    int err_code;
};

enum ReturnStatus ListCtor (struct StructList* list, int capacity);

void ListDtor(struct StructList* list);

int UserPrintList(struct StructList* list);

int Insert(struct StructList* list, int index, char* word);

int InsertAfter(struct StructList* list,
                int prev_index, const char* value);

int InsertBefore(struct StructList* list,
                 int index, const char* value);

int InsertBeforeHead(struct StructList* list,
                     const char* value);

int InsertAfterTail(struct StructList* list,
                     const char* value);

enum ReturnStatus DeleteElement(struct StructList* list,
                                int del_index);

enum ReturnStatus OpenLogFile();

enum ReturnStatus UpwardReallocate(struct StructList* list);

enum ReturnStatus DownwardReallocate(struct StructList* list, bool with_linearization);

enum ReturnStatus Linearization(struct StructList* list);

void CloseLogFile();

void SwapNode(struct StructList* list, int ind1, int ind2);

int SortListByNext(struct StructList* list);

#define INSERT_AFTER(list, index, element, label)                        \
    if ((ret_value = InsertAfter(list, index, element,                          \
                    __LINE__, __func__, __FILE__)) == -1) {      \
        goto label;                                                \
    }

#define INSERT_BEFORE(list, index, element, label)                        \
    if ((ret_value = InsertBefore(list, index, element,                          \
                    __LINE__, __func__, __FILE__)) == -1) {      \
        goto label;                                                \
    }

#define INSERT_BEFORE_HEAD(list, element, label)                        \
    if ((ret_value = InsertBeforeHead(list, element,                          \
                    __LINE__, __func__, __FILE__)) == -1) {      \
        goto label;                                                \
    }

#define INSERT_AFTER_TAIL(list, element, label)                        \
    if ((ret_value = InsertAfterTail(list, element,                          \
                    __LINE__, __func__, __FILE__)) == -1) {      \
        goto label;                                                \
    }

#define DELETE_ELEMENT(list, index, label)                        \
    if ((ret_value = DeleteElement(list, index,                          \
                    __LINE__, __func__, __FILE__)) == -1) {      \
        goto label;                                                \
    }

#endif
