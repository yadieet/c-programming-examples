#include "ysa_lib.h"
#include "ysa_dl_list.h"

void dl_list_init (struct DL_LIST *list)
{
    if (list == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }
    else
    {
        struct DL_LIST_NODE *sentinel = malloc(sizeof *sentinel);

        if (sentinel == NULL)
        {
            free(list);
            list = NULL;
            GET_ETIME(et);
            exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
        }
        else
        {
            sentinel->prev  = sentinel;
            sentinel->next  = sentinel;

            list->sentinel  = sentinel;
            list->ptrsig    = PTRSIG;
            list->is_static = true;
        }
    }
}

struct DL_LIST *dl_list_new ()
{
    struct DL_LIST *list = malloc(sizeof *list);

    if (list == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }
    else
    {
        struct DL_LIST_NODE *sentinel = malloc(sizeof *sentinel);

        if (sentinel == NULL)
        {
            free(list);
            list = NULL;
            GET_ETIME(et);
            exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
        }
        else
        {
            sentinel->prev  = sentinel;
            sentinel->next  = sentinel;

            list->sentinel  = sentinel;
            list->ptrsig    = PTRSIG;
            list->is_static = false;
        }
    }

    return list;
}

_Bool dl_list_is_empty (struct DL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    return (list->sentinel->next == list->sentinel);
}

void dl_list_add_first (void *data, struct DL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct DL_LIST_NODE *new_node = malloc(sizeof *new_node);
    if (new_node == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }

    new_node->data = data;
    new_node->prev = list->sentinel;

    new_node->next = list->sentinel->next;
    list->sentinel->next->prev = new_node;
    list->sentinel->next = new_node;
}

void dl_list_add_last (void *data, struct DL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct DL_LIST_NODE *new_node = malloc(sizeof *new_node);
    if (new_node == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }

    new_node->data = data;
    new_node->next = list->sentinel;

    new_node->prev = list->sentinel->prev;
    list->sentinel->prev->next = new_node;
    list->sentinel->prev = new_node;
}

void *dl_list_poll_first (struct DL_LIST *list)
{
    if ( dl_list_is_empty(list) )
        return NULL;

    struct DL_LIST_NODE *tmp   = list->sentinel->next;
    list->sentinel->next       = tmp->next;
    list->sentinel->next->prev = list->sentinel;

    void *data = tmp->data;
    free(tmp);

    return data;
}

void *dl_list_poll_last (struct DL_LIST *list)
{
    if ( dl_list_is_empty(list) )
        return NULL;

    struct DL_LIST_NODE *tmp   = list->sentinel->prev;
    list->sentinel->prev       = tmp->prev;
    list->sentinel->prev->next = list->sentinel;

    void *data = tmp->data;
    free(tmp);

    return data;
}

void dl_list_remove_all (struct DL_LIST *list, void (*func)(void *))
{
    if ( dl_list_is_empty(list) )
        return;

    if (func == NULL)
        func = do_nothing;

    struct DL_LIST_NODE *tmp;
    do
    {
        tmp = list->sentinel->next;
        list->sentinel->next       = tmp->next;
        list->sentinel->next->prev = list->sentinel;

        func(tmp->data);
        free(tmp);
    }
    while( list->sentinel->next != list->sentinel );
}

void dl_list_destroy_list (struct DL_LIST *list, void (*func)(void *))
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    dl_list_remove_all(list, func);

    list->ptrsig = '\0';
    free(list->sentinel);
    if ( !list->is_static )
        free(list);
}

unsigned int dl_list_count (struct DL_LIST *list)
{
    if ( dl_list_is_empty(list) )
        return 0;

    int n = 0;
    for(struct DL_LIST_NODE *node=list->sentinel->next; node!=list->sentinel; node=node->next)
        n++;

    return n;
}

void dl_list_for_each (void (*func)(void *, va_list *), struct DL_LIST *list, ...)
{
    if ( dl_list_is_empty(list) )
        return;

    if ( func == NULL )
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    va_list ap;
    for(struct DL_LIST_NODE *node=list->sentinel->next; node!=list->sentinel; node=node->next)
    {
        va_start (ap, list);
        (*func)(node->data, &ap);
        va_end(ap);
    }
}

void dl_list_for_each_bwd (void (*func)(void *, va_list *), struct DL_LIST *list, ...)
{
    if ( dl_list_is_empty(list) )
        return;

    if ( func == NULL )
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    va_list ap;
    for(struct DL_LIST_NODE *node=list->sentinel->prev; node!=list->sentinel; node=node->prev)
    {
        va_start (ap, list);
        (*func)(node->data, &ap);
        va_end(ap);
    }
}
