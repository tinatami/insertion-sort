/* linked list interface */
/* Specialized for integers. */

/* Handle to list data structure. */
struct list;

/* Handle to list node. */
struct node;

/* Initialise a linked list and return a pointer to it.
 * Return NULL on failure. */
struct list* list_init(void);

/* Cleanup linked list data structure.
 * Return 0 if succesful, 1 otherwise. */
int list_cleanup(struct list *l);

/* Return a pointer to a new list node that contains the
 * number num. Return NULL on failure. */
struct node* list_new_node(int num);

/* Add item to the front of the list.
 * Return 0 if succesful, 1 otherwise. */
int list_add(struct list *l, int num);

/* Add item to the back of the list.
 * Return 0 if succesful, 1 otherwise. */
int list_add_back(struct list *l, int num);

/* Return the first node of the list or NULL is list is empty. */
struct node* list_head(struct list *l);

/* Return the last node of the list or NULL is list is empty. */
struct node* list_tail(struct list *l);

/* Return list length. */
int list_length(struct list *l);

/* Return the data element of the list node. */
int list_node_data(struct node* n);

/* Return a pointer to the next node in the list or NULL if
 * 'n' is the last node in the list. */
struct node* list_next(struct node* n);

/* Return a pointer to the previous node in the list l or NULL if
 * 'n' is the first node in the list. */
struct node* list_prev(struct list* l, struct node* n);

/* Unlink node n from list l.
 * Return 0 if n was succesfully removed from list l,
 * return 1 if an error unoccured during unlinking. */
int list_unlink_node(struct list* l, struct node* n);

/* Free node n. */
void list_free_node(struct node* n);

/* Insert node n after node m in list l. Node n must already be unlinked.
 * Return 0 if n was succesfully inserted, 1 otherwise.  */
int list_insert_after(struct list* l, struct node* n, struct node* m);

/* Insert node n before node m in list l. Node n must already be unlinked.
 * Return 0 if n was succesfully inserted, 1 otherwise.  */
int list_insert_before(struct list* l, struct node* n, struct node* m);
