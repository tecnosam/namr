#include <stdio.h>
#include "stdlib.h"

#include "headers/network.h"
#include "headers/hashmap.h"


int update_response(char *response, int n, char *update);
int find_next_space(char *ptr, int offset);
unsigned char * extract_word(unsigned char *ptr, int start, int end);

int main() {

  int server_socket, client_socket;

  int key_end, value_end;

  char *key, response[BUFFER_SIZE];
  unsigned char *value, *payload;

  server_socket = create_server_socket();

  while (1) {

    client_socket = accept_client_connection(server_socket);

    payload = receive_from_client(client_socket);

    // Getter flag
    if (*payload == 'S') {

      key_end = find_next_space(payload, 0);
      value_end = find_next_space(payload, key_end+1);

      // Extract key and value from string
      key = (char *)extract_word(payload, 1, key_end);
      value = extract_word(payload, key_end+1, value_end);

      // store key value in global hashmap
      store_in_map(key, value);

      // "1" means success
      update_response(response, BUFFER_SIZE, "1");

      // We don't free the memory of key and value
      // as they are stored in the hashmap
    }

    else if (*payload == 'G') {

      // get the index of the last character of key
      key_end = find_next_space(payload, 0);

      key = (char *)extract_word(payload, 1, key_end);

      value = retrieve_from_map(key);

      update_response(response, BUFFER_SIZE, value);

      // Free memory allocated for the key
      free(key);
    }

    else {
      //response = (char *)payload;
      update_response(response, BUFFER_SIZE, (char *)payload);
    }

    send_to_client(client_socket, response);
    kill_connection(client_socket);
  }

  kill_connection(server_socket);

  return 0;
}


unsigned char * extract_word(unsigned char *ptr, int start, int end) {

  int word_length = end - start;

  // dynamically allocate memory for word
  unsigned char *word = malloc(word_length);

  int i = 0;

  while ((start+i) != end) {
    *(word + i) = *(ptr + start + i);

    i++;
  }

  return word;
}


int find_next_space(char *ptr, int offset) {

  int i = offset;

  // Loop If the character is neither null or a space
  while (*(ptr + i) != 32 && *(ptr + i) != 0) {
    i++;
  }

  return i;
}

int update_response(char *response, int n, char *update) {

  // First re-initialize response to 0
  for (int i = 0; i < n; i++) {
    *(response + i) = 0;
  }

  // distance from first null byte
  // to 0 is the length of the string
  int update_size = find_next_space(update, 0);

  // Update the response buffer with the
  // correct response
  for (int i = 0; i < update_size; i++) {
    *(response + i) = *(update + i);
  }

}
