#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "../include/list_functions.h"
#include "../include/dump_functions.h"
#include "../include/set_get_functions.h"

int main()
{
    atexit(CloseLogFile);

    struct StructList list = {};

    OpenLogFile();

    ListCtor(&list, 1);

    InsertAfterTail(&list, "HELLO");
    InsertAfterTail(&list, "GG");
    InsertAfterTail(&list, "ALLO");

    ListDump(&list, "<h3>Before linearization</h3>\n");

    ListDtor(&list);

    return 1;
}
