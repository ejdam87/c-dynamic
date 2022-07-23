
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdlib.h>
#include <stdbool.h>

struct node {

    void *data;
    struct node *next;
    struct node *prev;

};

typedef struct linked_list {

    struct node *first;
    struct node *last;

    size_t elem_size;
    size_t length;

} linked_list;


void print_int(void*);
bool compare_int(void*, void*);

struct node *create_node(void);
void destroy_node(struct node*);
void delete_node(struct node*);
void detach_node(linked_list*, struct node*);

int append_to_list(linked_list*, void*);
int prepend_to_list(linked_list*, void*);
struct node* pop_from_list(linked_list*);
struct node* popleft_from_list(linked_list*);
struct node* search_list(linked_list*, void*, bool (*comparator) (void*, void*));
void print_list(linked_list*, void (*elem_printer) (void*));
linked_list *init_list(size_t);
void destroy_list(linked_list*);

struct node *get_nth_list(linked_list*, size_t);
void remove_nth_list(linked_list*, size_t);
struct node *pop_nth_list(linked_list*, size_t);

#endif

