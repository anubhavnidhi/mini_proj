CC=gcc

CFLAGS= -lrt

all: client server pipe pipe_bw sharedmem rdtsc timeofday gettime socket socket_bw

client: client.c
	$(CC) $(CFLAGS) client.c -o client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

pipe: pipe.c
	$(CC) $(CFLAGS) pipe.c -o pipe

sharedmem: sharedmem.c
	$(CC) $(CFLAGS) sharedmem.c -o sharedmem

rdtsc: rdtsc.c rdtsc.h
	$(CC) $(CFLAGS) rdtsc.c rdtsc.h -o rdtsc

timeofday: timeofday.c
	$(CC) $(CFLAGS) timeofday.c -o timeofday

gettime:  gettime.c
	$(CC) $(CFLAGS) gettime.c -o gettime

socket: socket.c
	$(CC) $(CFLAGS) socket.c -o socket

clean:
	rm -f client server pipe rdtsc timeofday gettime socket pipe_bw socket_bw sharedmem

pipe_bw: pipe_bw.c
	$(CC) $(CFLAGS) pipe_bw.c -o pipe_bw

socket_bw: socket_bw.c
	$(CC) $(CFLAGS) socket_bw.c -o socket_bw
