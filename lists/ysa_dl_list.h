#pragma once

#define PTRSIG 0x5A

struct DL_LIST_NODE
{
    void *data;
    struct DL_LIST_NODE *next;
    struct DL_LIST_NODE *prev;
};

struct DL_LIST
{
    struct DL_LIST_NODE *sentinel;
    char ptrsig;
    bool is_static;
};

extern void dl_list_init (struct DL_LIST *list);
extern struct DL_LIST *dl_list_new ();
extern _Bool dl_list_is_empty (struct DL_LIST *list);
extern void dl_list_add_first (void *data, struct DL_LIST *list);
extern void dl_list_add_last (void *data, struct DL_LIST *list);
extern void *dl_list_poll_first (struct DL_LIST *list);
extern void *dl_list_poll_last (struct DL_LIST *list);
extern void dl_list_remove_all (struct DL_LIST *list, void (*func)(void *));
extern void dl_list_destroy_list (struct DL_LIST *list, void (*func)(void *));
extern unsigned int dl_list_count (struct DL_LIST *list);
extern void dl_list_for_each (void (*func)(void *, va_list *), struct DL_LIST *list, ...);
extern void dl_list_for_each_bwd(void (*func)(void *, va_list *), struct DL_LIST *list, ...);
