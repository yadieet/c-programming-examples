#include "ysa_lib.h"
#include "ysa_sl_list.h"

suppress_w(unused-parameter)
void print_data(void *data, va_list *args)
{
    end_suppress
    printf("<%d> ", *(int *) data);
}


void print_all(struct SL_LIST *list)
{
    if ( sl_list_is_empty(list) )
    {
        printf("<Empty>\n");
        return;
    }

    sl_list_for_each(print_data, list);
    puts("");
}

suppress_w(unused-parameter)
int ysacr_fatal_exception (struct etime *et, unsigned int errcode,
                                  const char *errmsg, const char *srcfile,
                                  unsigned int srcline)
{
    end_suppress
    puts("\n\n\
==============================================================================");
    printf(" ERROR/EXCEPTION, code %d", errcode);
    if (errmsg != NULL)
        printf(" : \"%s\"", errmsg);
    puts("");
    if (srcfile != NULL || srcline != 0)
        printf("   at ");
    if (srcfile != NULL)
        printf("`%s` ", srcfile);
    if (srcline != 0)
        printf("line %d\n", srcline);
    puts("==============================================================================");

    return 1;
}


int main(void)
{
    struct SL_LIST l, *list = &l;
    sl_list_init( list );

    if (list == NULL)
        return 1;

    {
        int i, *data;

        for (i=0; i<10; i++)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            sl_list_add(data, list);
            print_all(list);
        }

        sl_list_remove_all(list, free);
        print_all(list);
        puts("");

        for (i=0; i<10; i++)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            sl_list_add(data, list);
            print_all(list);
        }

        while( !sl_list_is_empty(list) )
        {
            data = sl_list_pop(list);
            printf("[%d] ", *data);
            free(data);
            print_all(list);
        }
        puts("");
    }

    sl_list_destroy_list(list, free);

    return 0;
}
