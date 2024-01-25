#ifndef HASHMAP_DIRECTIVES

  #define HASHMAP_DIRECTIVES
  #include "string.h"
  #include "stdio.h"

  #include "stdlib.h"

  #define HASHMAP_CAPACITY 10000000

#endif // ! HASHMAP_DIRECTIVES


typedef struct ValueNode {

  char *key;
  unsigned char *value;
  struct ValueNode *next;
} ValueNode;


ValueNode * table[HASHMAP_CAPACITY] = { NULL };

// Function Declarations

unsigned int hash_string(char *str);
void chain(ValueNode * current_value_node, ValueNode * next_value_node);
void store_in_map(char *key, unsigned char *value);
unsigned char * retrieve_from_map(char * key);


unsigned char * retrieve_from_map(char *key) {
  /*
   *
   * Retrieve from the hashmap, the value associated
   * with a key. Returns null if key not found.
   */

  unsigned int hashed_key = hash_string(key);

  ValueNode * first_match = table[hashed_key];

  while (first_match != NULL) {

    if (strcmp(key, first_match->key) == 0) {
      return first_match->value;
    }

    first_match = first_match->next;

  }

  return NULL;
}


void store_in_map(char *key, unsigned char * value) {

  unsigned int hashed_key = hash_string(key);

  ValueNode *new_value_node = (ValueNode *)malloc(sizeof(ValueNode));

  new_value_node->value = value;
  new_value_node->key = key;
  new_value_node->next = NULL;

  ValueNode *first_value_node = table[hashed_key];

  if (first_value_node == NULL) {
    table[hashed_key] = new_value_node;
  }
  else {
    chain(first_value_node, new_value_node);
  }

  return;

}


void chain(
  ValueNode * current_value_node,
  ValueNode * next_value_node
) {
  /*
  * Appends a node to the end of a Linked List
  * In this case, a value ValueNode
  */

  // if key already exists in hash map, just replace the value
  if (strcmp(current_value_node->key, next_value_node->key) == 0) {

    current_value_node->value = next_value_node->value;

    // free the memory occupied by the new node created
    free(next_value_node);
  }

  else if (current_value_node->next == NULL) {
    current_value_node->next = next_value_node;
  }
  else {
    chain(current_value_node->next, next_value_node);
  }

}


unsigned int hash_number(int number) {
  return number % HASHMAP_CAPACITY;
}


unsigned int hash_string(char *str) {

  int string_length = strlen(str);

  int sum = 0;

  for (int i = 0; i < string_length; i++) {

    // Add the ASCII int value of character
    sum += (int)(*(str + i));
  }

  return hash_number(sum);
}
