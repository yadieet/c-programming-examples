#pragma once

#define PTRSIG 0x5A

struct SL_LIST_NODE
{
    void *data;
    struct SL_LIST_NODE *prev;
};
struct SL_LIST
{
    struct SL_LIST_NODE *last_node;
    char ptrsig;
    bool is_static;
};

extern void sl_list_init (struct SL_LIST *list);
extern struct SL_LIST *sl_list_new ();
extern void sl_list_add (void *data, struct SL_LIST *list);
extern bool sl_list_is_empty (struct SL_LIST *list);
extern void *sl_list_pop (struct SL_LIST *list);
extern void sl_list_remove_all (struct SL_LIST *list, void (*func)(void *));
extern void sl_list_destroy_list (struct SL_LIST *list, void (*func)(void *));
extern unsigned int sl_list_count(struct SL_LIST *list);
extern void sl_list_for_each(void (*func)(void *, va_list *), struct SL_LIST *list, ...);
