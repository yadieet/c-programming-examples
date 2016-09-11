#include "ysa_lib.h"
#include "ysa_dl_list.h"

suppress_w(unused-parameter)
void print_data(void *data, va_list *args)
{
    end_suppress
    printf("<%d> ", *(int *) data);
}

void print_all_forward(struct DL_LIST *list)
{
    if ( dl_list_is_empty(list) )
    {
        printf("<Empty>\n");
        return;
    }

    dl_list_for_each(print_data, list);
    puts("");
}

void print_all_backward(struct DL_LIST *list)
{
    if ( dl_list_is_empty(list) )
    {
        printf("<Empty>\n");
        return;
    }

    dl_list_for_each_bwd(print_data, list);
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
    struct DL_LIST l, *list = &l;
    dl_list_init( list );

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
            dl_list_add_last(data, list);
            print_all_backward(list);
        }

        while( !dl_list_is_empty(list) )
        {
            data = dl_list_poll_last(list);
            printf("[%d] ", *data);
            free(data);
            print_all_backward(list);
        }
        puts("");

        for (i=0; i<10; i++)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            dl_list_add_first(data, list);
            print_all_backward(list);
        }

        while( !dl_list_is_empty(list) )
        {
            data = dl_list_poll_first(list);
            printf("[%d] ", *data);
            free(data);
            print_all_forward(list);
        }
        puts("");

        for (i=0; i<10; i++)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            dl_list_add_last(data, list);
            print_all_backward(list);
        }

        dl_list_remove_all(list, free);
        print_all_forward(list);
        puts("");

        for (i=0; i<10; i++)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            dl_list_add_first(data, list);
            print_all_backward(list);
        }

        while( !dl_list_is_empty(list) )
        {
            data = dl_list_poll_last(list);
            printf("[%d] ", *data);
            free(data);
            print_all_backward(list);
        }
        puts("");
    }

    dl_list_destroy_list(list, free);

    return 0;
}
