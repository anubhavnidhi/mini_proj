CC=gcc

CFLAGS= -lrt

all: client server pipe rdtsc timeofday

client: client.c
	$(CC) $(CFLAGS) client.c -o client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

pipe: pipe.c
	$(CC) $(CFLAGS) pipe.c -o pipe

rdtsc: rdtsc.c rdtsc.h
	$(CC) $(CFLAGS) rdtsc.c rdtsc.h -o rdtsc

timeofday: timeofday.c
	$(CC) $(CFLAGS) timeofday.c -o timeofday

clean:
	rm -f client server pipe rdtsc timeofday
