#include "ysa_lib.h"
#include "ysa_sl_list.h"

void sl_list_init (struct SL_LIST *list)
{
    if (list == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }
    else
    {
        list->last_node = NULL;
        list->ptrsig    = PTRSIG;
        list->is_static = true;
    }
}

struct SL_LIST *sl_list_new ()
{
    struct SL_LIST *list = malloc(sizeof *list);

    if (list == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }
    else
    {
        list->last_node = NULL;
        list->ptrsig    = PTRSIG;
        list->is_static = false;
    }

    return list;
}

void sl_list_add (void *data, struct SL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct SL_LIST_NODE *new_node = malloc(sizeof *new_node);
    if (new_node == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }

    new_node->data  = data;
    new_node->prev  = list->last_node;
    list->last_node = new_node;
}

bool sl_list_is_empty (struct SL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    return (list->last_node == NULL);
}

void *sl_list_pop (struct SL_LIST *list)
{
    if ( sl_list_is_empty(list) )
        return NULL;

    struct SL_LIST_NODE *tmp = list->last_node;
    list->last_node = tmp->prev; // list->last_node = list->last_node->prev;
    void *data = tmp->data;
    free(tmp);

    return data;
}

void sl_list_remove_all (struct SL_LIST *list, void (*func)(void *))
{
    if ( sl_list_is_empty(list) )
        return;

    if (func == NULL)
        func = do_nothing;

    struct SL_LIST_NODE *tmp;
    do
    {
        tmp = list->last_node;
        list->last_node = tmp->prev; //list->last_node = list->last_node->prev;
        func(tmp->data);
        free(tmp);
    }
    while( list->last_node != NULL );
}

void sl_list_destroy_list (struct SL_LIST *list, void (*func)(void *))
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    sl_list_remove_all(list, func);

    list->ptrsig = '\0';
    if ( !list->is_static )
        free(list);
}

unsigned int sl_list_count(struct SL_LIST *list)
{
    if ( sl_list_is_empty(list) )
        return 0;

    int n = 0;
    for(struct SL_LIST_NODE *node=list->last_node; node!=NULL; node=node->prev)
        n++;

    return n;
}

void sl_list_for_each(void (*func)(void *, va_list *), struct SL_LIST *list, ...)
{
    if ( sl_list_is_empty(list) )
        return;

    if ( func == NULL )
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    va_list ap;
    for(struct SL_LIST_NODE *node=list->last_node; node!=NULL; node=node->prev)
    {
        va_start (ap, list);
        (*func)(node->data, &ap);
        va_end(ap);
    }
}
