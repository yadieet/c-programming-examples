#pragma once

#define PTRSIG 0x5A

struct CL_LIST_NODE
{
    struct CL_LIST_NODE *prev, *next;
    unsigned long node_id;
    void *data;
};

struct CL_LIST
{
    struct CL_LIST_NODE *cursor;
    char ptrsig;
    unsigned long inc_node_id;
    bool is_static;
};

extern void cl_list_init (struct CL_LIST *list);
extern struct CL_LIST *cl_list_new ();
extern _Bool cl_list_is_empty (struct CL_LIST *list);
extern void cl_list_add_next (void *data, struct CL_LIST *list);
extern void cl_list_add_prev (void *data, struct CL_LIST *list);
extern _Bool cl_list_set_curr (unsigned long id, struct CL_LIST *list);
extern _Bool cl_list_set_curr_altn (unsigned long id, struct CL_LIST *list);
extern unsigned int cl_list_count (struct CL_LIST *list);
extern void cl_list_remove_all (struct CL_LIST *list, void (*func)(void *));
extern void cl_list_destroy_list (struct CL_LIST *list, void (*func)(void *));
extern void *cl_list_curr_poll (struct CL_LIST *list);
extern void *cl_list_poll (struct CL_LIST *list);
extern void *cl_list_curr_poll_altn (struct CL_LIST *list);
extern void *cl_list_poll_altn (struct CL_LIST *list);
extern unsigned long cl_list_curr_get_id (struct CL_LIST *list);
extern void *cl_list_curr_get_data (struct CL_LIST *list);
extern _Bool cl_list_curr_prev (struct CL_LIST *list);
extern _Bool cl_list_curr_next (struct CL_LIST *list);
extern _Bool cl_list_curr_move (unsigned int n, struct CL_LIST *list);
extern _Bool cl_list_curr_move_bwd (unsigned int n, struct CL_LIST *list);
extern void cl_list_for_each (void (*func)(unsigned long, void *, va_list *), struct CL_LIST *list, ...);
extern void cl_list_for_each_altn (void (*func)(unsigned long, void *, va_list *), struct CL_LIST *list, ...);
