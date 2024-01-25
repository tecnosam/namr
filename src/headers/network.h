#ifndef NETWORK_DIRECTIVES

  #define NETWORK_DIRECTIVES 1

  #include "stdio.h"
  #include "stdlib.h"
  #include "string.h"
  #include "unistd.h"
  #include "arpa/inet.h"

  #define PORT 9929
  #define BUFFER_SIZE 1024
  #define INTEGER_SIZE 4
#endif // !DEBUi


static char buffer[BUFFER_SIZE] = { 0 };

// declarations
void kill_connection(int socket);
void clear_buffer();
void send_to_client(int client_socket, char * payload);
char * receive_from_client(int client_socket);
int accept_client_connection(int server_socket);
int create_server_socket();


int create_server_socket() {

  int server_socket;
  struct sockaddr_in server_addr;

  // Creating socket file descriptor
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Binding the socket to the specified port
  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  // Listening for incoming connections
  if (listen(server_socket, 3) < 0) {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d\n", PORT);

  return server_socket;
}


int accept_client_connection(int server_socket) {
  struct sockaddr_in client_addr;

  socklen_t client_addr_len = sizeof(client_addr);

  int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

  if (client_socket < 0) {
    perror("Could not accept connection");

    exit(EXIT_FAILURE);
  }

  return client_socket;
}


char * receive_from_client(int client_socket) {

  clear_buffer();
  // Read packet of size payload_size
  read(client_socket, buffer, BUFFER_SIZE);

  return buffer;
}


void send_to_client(int client_socket, char * payload) {

  // Transmit the payload itself to client
  send(client_socket, payload, BUFFER_SIZE, 0);
}

void clear_buffer() {

  for (int i = 0 ; i < BUFFER_SIZE; i++) {
    *(buffer + i) = 0;
  }
}


void kill_connection(int socket) {
  close(socket);
}
