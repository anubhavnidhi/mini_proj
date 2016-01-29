CC=gcc

CFLAGS= -lrt

all: client server pipe

client: client.c
	$(CC) $(CFLAGS) client.c -o client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

pipe: pipe.c
	$(CC) $(CFLAGS) pipe.c -o pipe



clean:
	rm -f client server pipe
