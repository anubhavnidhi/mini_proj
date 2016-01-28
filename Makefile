CC=gcc
CFLAGS= -Wall -O -lrt

all: libudp sender receiver

sender: sender.c udp.o
	$(CC) $(CFLAGS) sender.c udp.o -o sender

receiver: receiver.c udp.o
	$(CC) $(CFLAGS) receiver.c udp.o -o receiver

libudp: udp.c
	$(CC) $(CFLAGS) -c udp.c -o udp.o

clean:
	rm -f udp.o sender receiver libudp.so