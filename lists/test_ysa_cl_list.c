#include "ysa_lib.h"
#include "ysa_cl_list.h"

suppress_w(unused-parameter)
void print_data(unsigned long id, void *data, va_list *args)
{
    end_suppress
    printf("<%d> ", *(int *) data);
}

void print_all(struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
    {
        puts("<Empty>\n");
        return;
    }

    cl_list_for_each(print_data, list);
    puts("");
}

void print_all_altn(struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
    {
        puts("<Empty>\n");
        return;
    }

    cl_list_for_each_altn(print_data, list);
    puts("");
}

void do_something(unsigned long id, void *data, va_list *args)
{
    int *tot = va_arg( *args, int *);
    *tot += *(int *) data;
    printf("%4lu : %d\n", id, *(int *) data);
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
    struct CL_LIST l, *list = &l;
    cl_list_init(list);

    if (list == NULL)
        return 1;

    {
        int i, *data;

        for (i=5; i<10; i++)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            cl_list_add_next(data, list);
        }
        cl_list_curr_next(list);
        for (i=4; i>-1; i--)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            cl_list_add_prev(data, list);
        }
        print_all(list);

        cl_list_curr_next(list);
        print_all(list);
        cl_list_curr_prev(list);
        print_all(list);
        cl_list_curr_move(2, list);
        print_all(list);
        cl_list_curr_move_bwd(2, list);
        print_all(list);
        cl_list_curr_prev(list);
        print_all(list);
        cl_list_curr_next(list);
        print_all(list);
        cl_list_curr_move_bwd(2, list);
        print_all(list);
        cl_list_curr_move(2, list);
        print_all(list);

        puts("");
        cl_list_remove_all(list, free);

        puts("");
        for (i=9; i>-1; i--)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            cl_list_add_prev(data, list);
        }
        print_all(list);
        puts("");

        puts("POLL TILL EMPTY :");
        while(!cl_list_is_empty(list))
        {
            data = cl_list_poll(list);
            printf("  [%d] ", *data);
            free(data);
            print_all(list);
        }

        puts("");
        for (i=9; i>-1; i--)
        {
            data = malloc(sizeof *data);
            if (data == NULL)
                return 1;
            *data = i;
            cl_list_add_prev(data, list);
        }
        print_all(list);
        puts("");

        puts("FOR EACH DO SOMETHING :");
        int total = 0;
        cl_list_for_each(do_something, list, &total);
        puts("~~~~~~~~~~~~ +");
        printf(" Tot : %d", total);
    }

    cl_list_destroy_list(list, free);

    return 0;
}
