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
    int ret_value = 0;

    struct StructList list = {};

    atexit(CloseLogFile);

    if (OpenLogFile())
        goto exit_label;

    if (ListCtor(&list, 11))
        goto exit_label;

    INSERT_AFTER(&list, 0, "HELLO", exit_label);

    INSERT_BEFORE_HEAD(&list, "GG", exit_label);

    INSERT_AFTER(&list, 2, "ALLO", exit_label);

    ListDump(&list, __LINE__, __func__, __FILE__,
             "<h3>Before linearization</h3>\n");

    exit_label:

        ListDtor(&list);

        if (ret_value != -1) {
            printf("END SUCCESS\n");
            return 0;
        }

        printf("END WITH ERROR\n");
        return 1;
}
