#include "ysa_lib.h"
#include "ysa_cl_list.h"

void cl_list_init (struct CL_LIST *list)
{
    if (list == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }
    else
    {
        list->cursor = NULL;
        list->ptrsig = PTRSIG;
        list->inc_node_id = 0L;
        list->is_static = true;
    }
}

struct CL_LIST *cl_list_new ()
{
    struct CL_LIST *list = malloc(sizeof *list);

    if (list == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }
    else
    {
        list->cursor = NULL;
        list->ptrsig = PTRSIG;
        list->inc_node_id = 0L;
        list->is_static = false;
    }

    return list;
}

_Bool cl_list_is_empty (struct CL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    return list->cursor == NULL;
}

void cl_list_add_next (void *data, struct CL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct CL_LIST_NODE *new_node = malloc(sizeof *new_node);
    if (new_node == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }

    new_node->node_id = ++(list->inc_node_id);
    new_node->data = data;

    if (list->cursor == NULL)
    {
        new_node->prev = new_node;
        new_node->next = new_node;
    }
    else
    {
        new_node->prev = list->cursor;
        new_node->next = list->cursor->next;
        list->cursor->next->prev = new_node;
        list->cursor->next = new_node;
    }

    list->cursor  = new_node;
}

void cl_list_add_prev (void *data, struct CL_LIST *list)
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct CL_LIST_NODE *new_node = malloc(sizeof *new_node);
    if (new_node == NULL)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 2, NULL, __FILE__, __LINE__ ) );
    }

    new_node->node_id = ++(list->inc_node_id);
    new_node->data = data;

    if (list->cursor == NULL)
    {
        new_node->prev = new_node;
        new_node->next = new_node;
    }
    else
    {
        new_node->next = list->cursor;
        new_node->prev = list->cursor->prev;
        list->cursor->prev->next = new_node;
        list->cursor->prev = new_node;
    }

    list->cursor  = new_node;
}

_Bool cl_list_set_curr (unsigned long id, struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return false;

    struct CL_LIST_NODE *node = list->cursor;
    do
    {
        if (node->node_id == id)
        {
            list->cursor = node;
            return true;
        }
    }
    while ( (node=node->next) != list->cursor);

    return false;
}

_Bool cl_list_set_curr_altn (unsigned long id, struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return false;

    struct CL_LIST_NODE *node = list->cursor;
    do
    {
        if (node->node_id == id)
        {
            list->cursor = node;
            return true;
        }
    }
    while ( (node=node->prev) != list->cursor);

    return false;
}

unsigned int cl_list_count (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return 0;

    int n = 0;

    struct CL_LIST_NODE *node = list->cursor;
    do
    {
        n++;
    }
    while ( (node=node->next) != list->cursor);

    return n;
}

void cl_list_remove_all (struct CL_LIST *list, void (*func)(void *))
{
    if ( cl_list_is_empty(list) )
        return;

    if (func == NULL)
        func = do_nothing;

    struct CL_LIST_NODE *tmp;

    while((tmp=list->cursor->next) != list->cursor)
    {
        tmp = list->cursor->next;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;

        func(tmp->data);
        free(tmp);
    }

    func(list->cursor->data);
    free(list->cursor);

    list->cursor = NULL;
    list->inc_node_id = 0L;
}

void cl_list_destroy_list (struct CL_LIST *list, void (*func)(void *))
{
    if (list->ptrsig != PTRSIG)
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    cl_list_remove_all(list, func);

    list->ptrsig = '\0';
    if ( !list->is_static )
        free(list);
}

void *cl_list_curr_poll (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return NULL;

    struct CL_LIST_NODE *tmp = list->cursor;

    if (tmp->next == tmp)
    {
        list->cursor = NULL;
        list->inc_node_id = 0L;
    }
    else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        list->cursor   = tmp->next;
    }

    void *data = tmp->data;
    free(tmp);

    return data;
}

void *cl_list_poll (struct CL_LIST *list)
{
    return cl_list_curr_poll(list);
}

void *cl_list_curr_poll_altn (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return NULL;

    struct CL_LIST_NODE *tmp = list->cursor;

    if (tmp->next == tmp)
    {
        list->cursor = NULL;
        list->inc_node_id = 0L;
    }
    else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        list->cursor   = tmp->prev;
    }

    void *data = tmp->data;
    free(tmp);

    return data;
}

void *cl_list_poll_altn (struct CL_LIST *list)
{
    return cl_list_curr_poll_altn(list);
}

unsigned long cl_list_curr_get_id (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return 0;

    return list->cursor->node_id;
}

void *cl_list_curr_get_data (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return NULL;

    return list->cursor->data;
}

_Bool cl_list_curr_prev (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return false;

    list->cursor = list->cursor->prev;
    return true;
}

_Bool cl_list_curr_next (struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return false;

    list->cursor = list->cursor->next;
    return true;
}

_Bool cl_list_curr_move (unsigned int n, struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return false;

    for( unsigned int i=0; i<n; i++)
        list->cursor = list->cursor->next;

    return true;
}

_Bool cl_list_curr_move_bwd (unsigned int n, struct CL_LIST *list)
{
    if ( cl_list_is_empty(list) )
        return false;

    for( unsigned int i=0; i<n; i++)
        list->cursor = list->cursor->prev;

    return true;
}

void cl_list_for_each (void (*func)(unsigned long, void *, va_list *), struct CL_LIST *list, ...)
{
    if ( cl_list_is_empty(list) )
        return;

    if ( func == NULL )
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct CL_LIST_NODE *node = list->cursor;

    va_list ap;
    do
    {
        va_start (ap, list);
        (*func)(node->node_id, node->data, &ap);
        va_end(ap);
    }
    while ( (node=node->next) != list->cursor);
}

void cl_list_for_each_altn (void (*func)(unsigned long, void *, va_list *), struct CL_LIST *list, ...)
{
    if ( cl_list_is_empty(list) )
        return;

    if ( func == NULL )
    {
        GET_ETIME(et);
        exit( ysacr_fatal_exception( &et, 1, NULL, __FILE__, __LINE__ ) );
    }

    struct CL_LIST_NODE *node = list->cursor;

    va_list ap;
    do
    {
        va_start (ap, list);
        (*func)(node->node_id, node->data, &ap);
        va_end(ap);
    }
    while ( (node=node->prev) != list->cursor);
}
