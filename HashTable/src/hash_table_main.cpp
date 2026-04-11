#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "list_functions.h"
#include "dump_functions.h"
#include "set_get_functions.h"

int main (void)
{
    atexit(CloseLogFile);

    struct StructList list = {};

    OpenLogFile();

    ListCtor(&list, 5);

    InsertAfter(&list, 0, 100,  __LINE__, __func__, __FILE__);

    ListDump(&list, __LINE__, __func__, __FILE__, "DUMP");

    ListDtor(&list);

}