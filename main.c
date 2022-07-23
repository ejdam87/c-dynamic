#include "linked_list.h"

int main() {

    linked_list *list = init_list(sizeof(int));

    for (int i = 0; i < 10; i++){

        prepend_to_list(list, &i);

    }

    print_list(list, print_int);

    struct node *nth = pop_nth_list(list, 9);

    print_list(list, print_int);

    destroy_list(list);

    return 0;
}
