#include <string.h>
#include "yourcode.h"

/// strdup equivalent since it does not always work on some machines
char *str(char *in)
{
  int len = strlen(in);
  char *out = calloc(len + 1, sizeof(char));
  for (int i = 0; i < len; ++i)
    {
      out[i] = in[i];
    }
  return out;
}

void create_random_lists(list_t **list1, list_t **list2)
{
  *list1 = list_create((void_cmp) strcmp);
  *list2 = list_create((void_cmp) strcmp);
                     
  char *strings[] = {"a", "b", "c", "d", "e", "f", "g", "h",
                     "i", "j", "k", "l", "m", "n", "o", "p",
                     "q", "r", "s", "t", "u", "v", "w", "x",
                     "y", "z"};
  int no_strings = 26;
  
  for (size_t input_size = 3 + (rand() % 3); input_size; --input_size)
    {
      int item = rand() % no_strings; 
      list_insert(*list1, str(strings[item]));
      strings[item] = strings[--no_strings]; 
    }
  
  for (size_t input_size = 3 + (rand() % 3); input_size; --input_size)
    {
      int item = rand() % no_strings; 
      list_insert(*list2, str(strings[item]));
      strings[item] = strings[--no_strings]; 
    }
}

void print(list_t *list)
{
    char *str = list_print(list, NULL);
    printf("'%s'\n", str);
    free(str);
}

bool link_check(link_t *links[], int size, link_t *first)
{
 for (int i = 0; i < size; ++i)
    {
      link_t *cursor = first;
      while (cursor)
        {
          if (cursor == links[i]) break;
          cursor = cursor->next;
        }
      if (cursor == NULL)
        {
          printf("Missing link with element %s\n", (char *)links[i]->element);
          return false; 
        }
    }
  return true;
}

void list_test()
{
  list_t *a = NULL; 
  list_t *b = NULL;
  create_random_lists(&a, &b);
  int size_a = list_size(a);
  int size_b = list_size(b);
  int size = size_a + size_b;

  puts("First random list 'a'");
  print(a);
  puts("Second random list 'b'");
  print(b);

  /// Recording pointer values
  link_t *links[size];
  int i = 0;
  for (link_t *cursor = list_first(a); cursor; cursor = cursor->next)
    {
      links[i++] = cursor; 
    }
  for (link_t *cursor = list_first(b); cursor; cursor = cursor->next)
    {
      links[i++] = cursor; 
    }
  
  puts("Merging lists");
  list_merge(a, b);

  puts("Expecting size of 'a' to be zero");
  printf("%d == %d ... %s\n", list_size(a), 0, (list_size(a) == 0 ? "PASSED" : "FAILED"));
  puts("Expecting size of 'b' to be sum of 'a' and 'b' before merge");
  printf("%d == %d ... %s\n", list_size(b), size, (list_size(b) == size ? "PASSED" : "FAILED"));

  puts("Expecting the output of 'a' to be []");
  print(a);
  puts("Expecting the output of 'b' to be all elements of 'a' and 'b' before merge in ascending order (e.g. a < b, b < c, etc.)");
  print(b);

  puts("Checking that the links, not just elements were moved");
  printf("... %s\n", link_check(links, size, list_first(b)) ? "PASSED" : "FAILED");
  
  list_destroy(a);
  list_destroy(b);
}

void empty_list_test()
{
  list_t *a = list_create((void_cmp) strcmp); 
  list_t *b = list_create((void_cmp) strcmp);

  puts("=========================== TEST 2 =================================");
  print(a);
  print(b);
  
  puts("Expecting size of a to be 0");
  printf("%d == %d ... %s\n", list_size(a), 0, list_size(a) == 0 ? "PASSED" : "FAILED");
  puts("Expecting size of b to be 0");
  printf("%d == %d ... %s\n", list_size(b), 0, list_size(b) == 0 ? "PASSED" : "FAILED");

  list_insert(a, strdup("a"));
  list_insert(a, strdup("b"));
  list_insert(a, strdup("c"));

  puts("Expecting size of a to be 3");
  printf("%d == %d ... %s\n", list_size(a), 3, list_size(a) == 3 ? "PASSED" : "FAILED");

  print(a);
  print(b);
  
  list_merge(a, b);
  
  puts("Expecting size of a to be 0 after merge");
  printf("%d == %d ... %s\n", list_size(a), 0, list_size(a) == 0 ? "PASSED" : "FAILED");
  puts("Expecting size of b to be 3 after merge");
  printf("%d == %d ... %s\n", list_size(b), 3, list_size(b) == 3 ? "PASSED" : "FAILED");

  print(a);
  print(b);
  list_destroy(a);
  list_destroy(b);
}

int main(void)
{
  for (int i = 0; i < 3; ++i)
    {
      puts("=========================== TEST START =================================");
      list_test();
      empty_list_test();
      puts("=========================== TEST STOP ==================================\n");
    }
  
  return 0;
}
