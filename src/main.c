#include <stdio.h>

#include "headers/network.h"


void setter(char *key, unsigned char *value);

unsigned char * getter(char *key);

int main() {

  int server_socket, client_socket;

  char * payload;

  server_socket = create_server_socket();

  while (1) {

    client_socket = accept_client_connection(server_socket);

    payload = receive_from_client(client_socket);

    send_to_client(client_socket, payload);

    printf("Received payload %s from client\n", payload);

    kill_connection(client_socket);
  }

  kill_connection(server_socket);

  return 0;
}


void setter(char *key, unsigned char *value) {

  return;
}

unsigned char * getter(char *key) {
  return "Not Implemented";
}
