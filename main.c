/* Tina Tami
 *
 * This file contains the mysort algorithm: it takes
 * as input a string of numbers, and returns the list
 * in the correct order. Additional features before
 * or after ordering are available.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>

#include "list.h"

struct config {
    // Set to 1 if -u is specified, 0 otherwise.
    int remove_duplicates;

    // Set to 1 if -S is specified, 0 otherwise.
    int add_sum;

    // Set to N if -s N is specified, 0 otherwise.
    int select_multiple;

    // Set to N if -x N is specified, 0 otherwise.
    int remove_multiple;

    // Set to N if -h N is specified, 0 otherwise.
    int show_first;

    // Set to N if -t N is specified, 0 otherwise.
    int show_last;

    // Set to 1 if -3 is specified, 0 otherwise.
    int scribble;
};

static
int parse_options(struct config *cfg, int argc, char *argv[]);
struct list* mysort(struct list* unsorted_list);
int greater(struct node* n1, struct node* n2);
void list_print(struct list* sorted_list);
struct list* show_first(struct list* sorted_list, int n);
struct list* show_last(struct list* sorted_list, int n);
int add_sum(struct list* sorted_list);
struct list* remove_duplicates(struct list* sorted_list); 

#define BUF_SIZE 1024
static char buf[BUF_SIZE];
static char* split_line;

/* This is the main function. It reads the input, ignores 
 * enters and splits a line on white space to make sure we 
 * take in to account multiple digits on one line. Then, it 
 * carries out the sorting restrictions pre sorting. After 
 * sorting the list, it carries out the sorting restrictions
 * post sorting. Finally, it prints out the correct list. */
int main(int argc, char *argv[]) {
    struct config cfg;
    if (parse_options(&cfg, argc, argv) != 0)
        return 1;
    struct list* unsorted_list = list_init();
    int input;
    int line_number = 1;
    while (fgets(buf, BUF_SIZE, stdin)) {
        if (cfg.remove_multiple != 0) {
            if (line_number % cfg.remove_multiple == 0) {
                line_number++;
                continue; 
            }
        }
        if (cfg.select_multiple != 0) {
            if (line_number % cfg.select_multiple != 0) {
                line_number++;
                continue; 
            }
        }
        if (buf[0] == '\n') {
            continue;
        }
        split_line = strtok(buf, " ");
        while (split_line != NULL) {
            input = atoi(split_line);
            if (cfg.scribble == 1) {
                if (input == 42 || input == 51 || input == 69) {
                    input = 666;
                }
            }
            list_add(unsorted_list, input);
            split_line = strtok(NULL, " ");
        }
        line_number++;
    }
    struct list* sorted_list = mysort(unsorted_list);
    if (cfg.show_first != 0) {
        sorted_list = show_first(sorted_list, cfg.show_first);
    }
    if (cfg.show_last != 0) {
        sorted_list = show_last(sorted_list, cfg.show_last);
    }
    if (cfg.remove_duplicates == 1) {
        remove_duplicates(sorted_list);
    }
    if (cfg.add_sum == 1) {
        add_sum(sorted_list);
    } 
    list_print(sorted_list);
    list_cleanup(sorted_list);
    return 0;
}

/* This is the main insertion sort algorithm. It reads one number at a
 * time from the input. Then, it looks for the correct position 
 * in the sorted list. */
struct list* mysort(struct list* unsorted_list) {
    struct list* sorted_list = list_init(); 
    struct node* temp_head;
    struct node* unsorted_head; 
    while (list_head(unsorted_list) != NULL) {
        unsorted_head = list_head(unsorted_list); 
        list_unlink_node(unsorted_list, unsorted_head); 
        temp_head = list_head(sorted_list); 
        if (temp_head == NULL) { 
            list_add(sorted_list, list_node_data(unsorted_head)); 
            list_free_node(unsorted_head); 
        }
        else { 
            while (greater(unsorted_head, temp_head) == 1) { 
                temp_head = list_next(temp_head); 
            }
            if (temp_head == NULL) {
                list_add_back(sorted_list, list_node_data(unsorted_head));
                list_free_node(unsorted_head);
            }
            else if (greater(unsorted_head, temp_head) == 0) { 
                list_insert_before(sorted_list, unsorted_head, temp_head); 
            }
        }
    }
    list_cleanup(unsorted_list);
    return sorted_list;
}

/* This checks if n1 (node 1) is greater than n2 (node 2). 
 * Returns 1 if true, 0 if false, and -1 if n2 does not exist. */
int greater(struct node* n1, struct node* n2) {
    if (n2 == NULL) {
        return -1;
    }
    else if (list_node_data(n1) > list_node_data(n2)) {
        return 1;
    }
    return 0;
}

/* This prints the sorted list. */
void list_print(struct list* sorted_list) {
    if (list_head(sorted_list) == NULL) {
        printf("This list is empty.\n");
    }
    else {
        struct node* temp_head = list_head(sorted_list);
        while (list_next(temp_head) != NULL) {
            printf("%d\n", list_node_data(temp_head));
            temp_head = list_next(temp_head);
        }
        printf("%d\n", list_node_data(temp_head));
    }
}

/* Puts the first n numbers of the sorted list into a new list, 
 * makes that the new sorted list and returns it. */
struct list* show_first(struct list* sorted_list, int n) {
    struct list* list_show_first = list_init();
    if (n < list_length(sorted_list)) {
        struct node* temp_head;
        for (int i = 0; i < n; i++) { 
            temp_head = list_head(sorted_list);
            list_add_back(list_show_first, list_node_data(temp_head));
            list_unlink_node(sorted_list, temp_head);
        }
        list_free_node(temp_head);
    }
    return list_show_first;
}

/* Unlinks the numbers that you do not want to show, returns a list with
 * the n numbers you want to show.  */
struct list* show_last(struct list* sorted_list, int n) {
    int do_not_show = list_length(sorted_list) - n;
    struct node* temp_head;
    for (int i = 0; i < do_not_show; i++) {
        temp_head = list_head(sorted_list);
        list_unlink_node(sorted_list, temp_head);
    }
    list_free_node(temp_head);
    return sorted_list;
}

/* Adds the sum of all the nodes to the end of the list. */
int add_sum(struct list* sorted_list) {
    int sum = 0;
    struct node* temp_head = list_head(sorted_list);
    while (temp_head != NULL) {
        sum += list_node_data(temp_head);
        temp_head = list_next(temp_head);
    }
    return list_add_back(sorted_list, sum);
}

/* Removes duplicates in the sorted list. */
struct list* remove_duplicates(struct list* sorted_list) {
    if (sorted_list != NULL) {
        struct node* n1 = list_head(sorted_list);
        struct node* n2;
        while (list_next(n1) != NULL) {
            n2 = list_next(n1);
            if (list_node_data(n1) == list_node_data(n2)) {
                list_unlink_node(sorted_list, n1);
                list_free_node(n1);
            }
            n1 = n2;
        }
    }
    return sorted_list;
}

int parse_options(struct config *cfg, int argc, char *argv[]) {
    memset(cfg, 0, sizeof(struct config));
    int c;
    while ((c = getopt (argc, argv, "uSs:x:h:t:3")) != -1)
        switch (c) {
        case 'u': cfg->remove_duplicates = 1; break; 
        case 'S': cfg->add_sum = 1; break; 
        case '3': cfg->scribble = 1; break; 
        case 's': cfg->select_multiple = atoi(optarg); break; 
        case 'x': cfg->remove_multiple = atoi(optarg); break; 
        case 'h': cfg->show_first = atoi(optarg); break; 
        case 't': cfg->show_last = atoi(optarg); break; 
        default:
            fprintf(stderr, "invalid option: -%c\n", optopt);
            return 1;
        }
    if (cfg->show_first != 0 && cfg->show_last != 0) {
        fprintf(stderr, "cannot specify both -h and -t\n");
        return 1;
    }
    return 0;
}
