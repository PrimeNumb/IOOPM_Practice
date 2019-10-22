#define _GNU_SOURCE

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "yourcode.h"

struct list
{
  link_t *first;
  link_t *last;
  void_cmp cmp;
};

static link_t *link_create(link_t *next, void *element)
{
  link_t *link = malloc(sizeof(link_t));
  link->next = next;
  link->element = element;
  return link;
}

list_t *list_create(void_cmp cmp)
{
  list_t *list = malloc(sizeof(list_t));
  list->first = list->last = link_create(NULL, NULL); /// Dummy!
  list->cmp = cmp;
  return list;
}

void list_insert(list_t *list, void *element)
{
  link_t *cursor = list->first;
  
  while (cursor->next && list->cmp(cursor->next->element, element) < 0)
    {
      cursor = cursor->next;
    }

  if (cursor->next)
    {
      if (list->cmp(cursor->next->element, element))
        {
          cursor->next = link_create(cursor->next, element);
        }
      else
        {
          cursor->next->element = element;
        }
    }
  else
    {
      list->last = cursor->next = link_create(NULL, element);
    }
}

int list_size(list_t *list)
{
  /// TODO
  if(!list || !list->first)
    return 0;

  
  int size = 0;

  link_t *cursor = list->first->next;

  while(cursor)
  {
    cursor = cursor->next;
    size++;
  }
  /// Returnera antalet element i listan. Detta skall räknas ut
  /// genom iteration över samtliga länkar.
  return size; 
}

void list_destroy(list_t *list)
{
  if(list)
  {
    link_t *to_remove = list->first;

    while(to_remove)
    {
      link_t *next_link = to_remove->next; //cache the next link
      
      free(to_remove->element); //free the element
      free(to_remove);
      to_remove = next_link;
    }
    //both first and last pointers are covered by the above!
    free(list);
  }
  /// Ta bort listan, alla länkar och alla länkars alla element
}


/// Alla länkar (och dess medföljande element, dock ej dummies)
/// skall flyttas från source till dest.
void list_merge(list_t *source, list_t *dest)
{
  /// TODO
  if(source && dest)
  {
    link_t *src_cursor = source->first->next;

    //Disconnect the chain of links from the dummy
    source->first->next = NULL;
    
    while(src_cursor)
    {
      link_t *dest_cursor = dest->first;
      
      //Cache the link to be moved
      link_t *link_to_move = src_cursor;

      //Move the source cursor forward
      src_cursor = src_cursor->next;

      //-----------------------------------------
      //Insert the link into the destination list

      //Move the cursor to the link previous to the one we want to insert to
      while(dest_cursor->next && dest->cmp(dest_cursor->next->element, link_to_move->element) < 0)
      {
	dest_cursor = dest_cursor->next;
      }

      //If there's a link ahead of us, link the links (heh)
      if(dest_cursor->next)
      {
        link_to_move->next = dest_cursor->next;
	dest_cursor->next = link_to_move;
      }
      else //otherwise we can just put the link ahead of us
      {
	dest_cursor->next = link_to_move;
	link_to_move->next = NULL;

	//move the last pointer
	dest->last = link_to_move;
      }
    }
    source->last = source->first;
  }
}  

/// Returns a string representation of the list to be printed
/// No need to read or change this function!!
char *list_print(list_t *list, elem_to_string to_string)
{
  char *result = calloc(2048, sizeof(char));
  strcat(result, "[");
  
  for (link_t *cursor = list->first->next; cursor; cursor = cursor->next)
    {
      char *tmp = NULL;
      asprintf(&tmp, "%s, ", to_string ? to_string(cursor->element) : (char *)cursor->element);
      strcat(result, tmp);
      free(tmp);
    }

  int size = strlen(result);
  strcpy(result + (size > 1 ? size - 2 : size), "]");
  
  return result;
}

/// Return the first link in the list for testing
/// No need to read or change this function!!
link_t *list_first(list_t *list)
{
  return list->first->next;
}
