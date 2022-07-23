#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Example helpers

void print_int(void *elem){
    printf("%d", *(int *) elem);
}

bool compare_int(void *a, void *b){
    return *(int*) a == *(int*) b;
}

// ---


linked_list *init_list(size_t elem_size){

    linked_list * list = malloc(sizeof(linked_list));
    list -> elem_size = elem_size;
    list -> length = 0;
    list -> first = NULL;
    list -> last = NULL;
    return list;

}

void destroy_list(linked_list *list){

    struct node *node = list -> first;
    if (node == NULL){
        return;
    }

    struct node *next;

    while (node != NULL){

        next = node -> next;

        destroy_node(node);
        free(node);

        node = next;

    }

    free(list);

}

struct node *create_node(void){

    struct node *new_node = malloc(sizeof(struct node));

    if (new_node == NULL){
        return NULL;
    }

    new_node -> data = NULL;
    new_node -> next = NULL;
    new_node -> prev = NULL;

    return new_node;
}

int fill_node(linked_list *list, struct node *node, void *elem){

    if (node == NULL){
        return 1;
    }

    node -> data = malloc(list -> elem_size);
    memcpy(node -> data, elem, list -> elem_size);
    return 0;

}

void delete_node(struct node *node){

    destroy_node(node);
    free(node);

}

void destroy_node(struct node *node){

    free(node -> data);

}

void detach_node(linked_list *list, struct node *node){

    if (node -> prev != NULL){
        node -> prev -> next = node -> next;
    }
    else {
        list -> first = node -> next;
    }

    if (node -> next != NULL){
        node -> next -> prev = node -> prev;
    }
    else {
        list -> last = node -> prev;
    }


    if (list -> length == 1){
        list -> first = NULL;
        list -> last = NULL;
    }

}

int append_to_list(linked_list *list, void *elem){

    struct node *node = create_node();
    if (fill_node(list, node, elem) == 1){
        return 1;
    }

    if (list -> last == NULL){

        list -> first = node;
        list -> last = node;
        list -> length++;
        return 0;

    }

    list -> last -> next = node;
    node -> prev = list -> last;
    list -> last = node;
    list -> length++;
    return 0;

}

int prepend_to_list(linked_list *list, void *elem){

    struct node *node = create_node();
    if (fill_node(list, node, elem) == 1){
        return 1;
    }

    if (list -> first == NULL){
        list -> first = node;
        list -> last = node;
        list -> length++;
        return 0;
    }

    node -> next = list -> first;
    list -> first -> prev = node;
    list -> first = node;
    list -> length++;

    return 0;

}

struct node* pop_from_list(linked_list *list){

    if (list -> length == 0){
        return NULL;
    }

    struct node *lst = list -> last;
    list -> last = list -> last -> prev;

    if (list -> last == NULL) {
        list -> first = NULL;
    }
    else if (list -> last == list -> first) {
        list -> last -> next = NULL;
        list -> last -> prev = NULL;
        list -> first -> next = NULL;
        list -> first -> prev = NULL;
    }
    else {
        list -> last -> next = NULL;
    }

    list -> length--;
    return lst;

}

struct node* popleft_from_list(linked_list *list){

    if (list -> first == NULL){
        return NULL;
    }

    struct node *fst = list -> first;
    list -> first = list -> first -> next;

    if (list -> first == NULL) {
        list -> last = NULL;
    }
    else if (list -> last == list -> first) {
        list -> last -> next = NULL;
        list -> last -> prev = NULL;
        list -> first -> next = NULL;
        list -> first -> prev = NULL;
    }
    else {
        list -> first -> prev = NULL;
    }

    list -> length--;
    return fst;

}

struct node *search_list(linked_list *list, void* val, bool (*comparator) (void*, void*)){

    for (struct node *current = list -> first; current != NULL; current = current -> next){

        if (comparator(current -> data, val)){
            return current;
        }
    }

    return NULL;

}


struct node *get_nth_list(linked_list *list, size_t n){

    if (n >= list -> length){
        return NULL;
    }

    struct node *nth_node = list -> first;

    for (int i = 0; i < n; i++){

        if (nth_node == NULL){
            return NULL;
        }

        nth_node = nth_node -> next;

    }

    return nth_node;

}

void remove_nth_list(linked_list *list, size_t n){

    struct node *nth_node = get_nth_list(list, n);

    if (nth_node == NULL){
        return;
    }

    detach_node(list, nth_node);
    list -> length--;
    delete_node(nth_node);

}

struct node *pop_nth_list(linked_list *list, size_t n){

    struct node *nth_node = get_nth_list(list, n);
    if (nth_node == NULL){
        return NULL;
    }

    detach_node(list, nth_node);
    list -> length--;
    return nth_node;

}

void print_list(linked_list *list, void (*elem_printer) (void*)){

    for (struct node *node = list -> first; node != NULL; node = node -> next){
        elem_printer(node -> data);
        printf(" -> ");
    }

    putchar('\n');

}