#include "stdio.h"

#include "headers/hashmap.h"


int main() {
  
  char *key = "kopal";

  char *key_that_collides = "kpoal";

  unsigned char *value = "192.186.43.105:9000";

  unsigned char *value_2 = "10.34.12.34:9000";

  printf("Value we store (%s) on key (%s) \n", value, key);

  printf("hash of string %d\n", hash_string("BA"));

  store_in_map(key, value);
  printf("Stored\n");

  unsigned char * retrieved_value = retrieve_from_map(key);
  printf("Value we stored %s. Value we received %s\n", value, retrieved_value);

  // Testing replacing a particular key
  store_in_map(key, value_2);
  retrieved_value = retrieve_from_map(key);

  printf("Former Value %s, new value %s\n", value, retrieved_value);

  // Key not stored
  char *invalid_key = "Sandy";
  unsigned char * should_be_null = retrieve_from_map(invalid_key);
  printf("Value should be null %s\n", should_be_null);

  printf("Testing key collision\n");
  store_in_map(key_that_collides, "Collided Ya'll");

  retrieved_value = retrieve_from_map(key);
  unsigned char * retrieved_value_2 = retrieve_from_map(key_that_collides);

  printf("Key 1 %s, Key 2 %s\n", retrieved_value, retrieved_value_2);

  return 0;
}
