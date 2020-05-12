CC = gcc
all: socket_client socket_server 
socket_server: socket_server.c
	$(CC) socket_server.c -o $@
socket_client: socket_client.c
	$(CC) socket_client.c -o $@
clean:
	rm -f socket_server socket_client
