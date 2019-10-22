#ifndef __yourcode__
#define __yourcode__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef int(*void_cmp)(void *e1, void *e2);
typedef char *(*elem_to_string)(void *e);

typedef struct link link_t;
typedef struct list list_t;

struct link
{
  link_t *next;
  void *element;
};

/// Create a new sorted (empty) list -- compare is a function that defines the sort order for the elements.
list_t *list_create(void_cmp compare);
/// Insert element into list according to the sort order
void list_insert(list_t *list, void *element);
/// Merge the two lists into dest, leaving source empty (note: implemented so that links move, not just elements!)
void list_merge(list_t *source, list_t *dest);
/// Return the number of elements in the list
int list_size(list_t *list);
/// Remove the list and its elements from memory
void list_destroy(list_t *list);
/// Return the string representation for the list, e.g. [a, b, c]
char *list_print(list_t *list, elem_to_string to_string);
/// Return the first link in the list for testing
link_t *list_first(list_t *list);

#endif

