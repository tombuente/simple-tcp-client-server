CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: server client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CFLAGS) client.c -o client

clean:
	rm -f client server *.o
