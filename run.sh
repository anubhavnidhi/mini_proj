#!/bin/bash

echo "SOCKET LATENCY"
./socket 4 100
./socket 16 100
./socket 64 100
./socket 256 100
./socket 1024 100
./socket 4096 100
./socket 16384 100
./socket 65536 100
./socket 262144 100
./socket 524288 100

echo "PIPE LATENCY"
./pipe 4 100
./pipe 16 100
./pipe 64 100
./pipe 256 100
./pipe 1024 100
./pipe 4096 100
./pipe 16384 100
./pipe 65536 100
./pipe 262144 100
./pipe 524288 100

echo "SHARED MEMORY LATENCY"
rm -f buf.txt
./sharedmem 4 100
./sharedmem 16 100
./sharedmem 64 100
./sharedmem 256 100
./sharedmem 1024 100
./sharedmem 4096 100
./sharedmem 16384 100
./sharedmem 65536 100
./sharedmem 262144 100
./sharedmem 524288 100
