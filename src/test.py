import socket

def tcp_client(server_ip, server_port, message):
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    server_address = (server_ip, server_port)
    client_socket.connect(server_address)

    try:
        # Send data
        client_socket.sendall(message.encode())

        # Receive response
        response = client_socket.recv(1024)
        print(f"Received response: {response.decode()}")

    finally:
        # Close the socket
        client_socket.close()

# Example usage
server_ip = '127.0.0.1'  # Replace with the actual server IP
server_port = 9929      # Replace with the actual server port

message = 'Skopal 192.168.43.105:9000'
tcp_client(server_ip, server_port, message)


message = 'Gkopal'
tcp_client(server_ip, server_port, message)

