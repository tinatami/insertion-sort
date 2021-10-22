/* Tina Tami
 *
 * This file contains the data structure described
 * in the list.h file. */

#include "list.h"
#include "stdlib.h"
#include <stdio.h>
#include <ctype.h>

struct list {
    struct node* head;
};
 
struct node {
    int data;
    struct node* next;
};

/* Initialises a linked list and returns a pointer to it. */
struct list* list_init() {
    struct list* l = malloc(sizeof (struct list));
    l -> head = NULL;
    if (l == NULL) {
        return NULL;
    }
    return l;
}

/* Cleans linked list data structure. */
int list_cleanup(struct list *l) {
    struct node* current = l -> head;
    struct node* temp;
    while (current != NULL) {
        temp = current;
        current = temp -> next;
        free(temp);
    }
    free(l);
    return 0;
}

/* Returns a pointer to a new list node that contains the
 * number num. */
struct node* list_new_node(int num) {
    if (isdigit(num) == 0) {
        return NULL;
    }
    struct node* new_node = malloc(sizeof (struct node));
    new_node -> data = num;
    new_node -> next = NULL;
    return new_node;
}

/* Adds item to the front of the list. */
int list_add(struct list *l, int num) {
    if (l == NULL) {
        return 1;
    }
    else if (l -> head == NULL) {
        struct node* new_node = malloc(sizeof (struct node));
        new_node -> data = num;
        new_node -> next = NULL;
        l -> head = new_node;
    }
    else if (l -> head != NULL) {
        struct node* new_node = malloc(sizeof (struct node));
        struct node* current;
        new_node -> data = num;
        current = l -> head;
        new_node -> next = current;
        l -> head = new_node;
    }
    return 0;
}

/* Adds item to the back of the list. */
int list_add_back(struct list *l, int num) {
    if (l == NULL) {
        return 1;
    }
    if (l -> head == NULL) {
        struct node* new_node = malloc(sizeof (struct node));
        new_node -> data = num;
        new_node -> next = NULL;
        l -> head = new_node;
    }
    else {
        struct node* current = l -> head;
        while (current -> next != NULL) {
            current = current -> next;
        }
        struct node* new_node = malloc(sizeof (struct node));
        new_node -> data = num;
        new_node -> next = NULL;
        current -> next = new_node;
    }
    return 0;
}

/* Returns the first node of the list or NULL if list is empty. */
struct node* list_head(struct list *l) {
    if (l -> head == NULL) {
        return NULL;
    }
    return l -> head;
}

/* Returns the last node of the list or NULL is list is empty. */
struct node* list_tail(struct list *l) {
    if (l -> head == NULL) {
        return NULL;
    }
    struct node* current = l -> head;
    while (current -> next != NULL) {
        current = current -> next;
    }
    return current;
}

/* Returns list length. */
int list_length(struct list *l) {
    if (l -> head == NULL || l == NULL) {
        return 0;
    }
    int length = 0;
    struct node* current = l -> head;
    while (current != NULL) {
        length++;
        current = current -> next;
    }
    return length; 
}

/* Returns the data element of the list node. */
int list_node_data(struct node* n) {
    return n -> data;
}

/* Returns a pointer to the next node in the list or NULL if
 * 'n' is the last node in the list. */
struct node* list_next(struct node* n) {
    if (n -> next == NULL) {
        return NULL;
    }
    return n -> next; 
}

/* Returns a pointer to the previous node in the list l or NULL if
 * 'n' is the first node in the list. */
struct node* list_prev(struct list* l, struct node* n) {
    if (n -> next == NULL && n == l -> head) {
        return NULL;
    }
    struct node* current = l -> head;
    while (current -> next != n) {
        current = current -> next;
    }
    return current;
}

/* Unlinks node n from list l.  */
int list_unlink_node(struct list* l, struct node* n) {
    if (l == NULL || n == NULL) {
        return 1;
    }
    else if (l -> head == n) {
        l -> head = n -> next;
        n -> next = NULL;
        return 0;
    }
    else if (l -> head != NULL && l -> head != n) {
        struct node* prev = list_prev(l, n);
        prev -> next = n -> next;
        n -> next = NULL;
        return 0;
    }
    return 1;
}

/* Frees node n. */
void list_free_node(struct node* n) {
    free(n);
}

/* Inserts node n after node m in list l. Node n must already be unlinked.
 * Returns 0 if n was succesfully inserted, 1 otherwise.  */
int list_insert_after(struct list* l, struct node* n, struct node* m) {
    if (n == NULL || m == NULL || l == NULL) {
        return 1;
    }
    struct node* current = l -> head;
    while (current != m) {
        current = current -> next;
    }
    n -> next = m -> next;
    m -> next = n;
    return 0;
}

/* Inserts node n before node m in list l. Node n must already be unlinked.
 * Returns 0 if n was succesfully inserted, 1 otherwise.  */
int list_insert_before(struct list* l, struct node* n, struct node* m) {
    if (n == NULL || m == NULL || l == NULL) {
        return 1;
    }
    else if (l -> head == m) {
        l -> head = n;
        n -> next = m;
    }
    else if (l -> head != m) {
        struct node* prev = list_prev(l, m);
        prev -> next = n;
        n -> next = m;
    }
    return 0;
}
