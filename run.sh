make

echo "Sockets Latency"

./socket 4 1000
./socket 16 1000
./socket 64 1000
./socket 256 1000
./socket 1024 1000
./socket 4096 1000
./socket 16384 1000
./socket 65536 500
./socket 262144 30
./socket 524288 3

echo "Sockets Bandwidth"

./socket_bw 1024 1000
./socket_bw 4096 1000
./socket_bw 16384 1000
./socket_bw 65536 500
./socket_bw 262144 30
./socket_bw 524288 3

echo "Pipe Latency"

./pipe 4 1000
./pipe 16 1000
./pipe 64 1000
./pipe 256 1000
./pipe 1024 1000
./pipe 4096 1000
./pipe 16384 1000
./pipe 65536 1000
./pipe 262144 1000
./pipe 524288 1000

echo "Pipe Bandwidth"

./pipe_bw 1024 1000
./pipe_bw 4096 1000
./pipe_bw 16384 1000
./pipe_bw 65536 1000
./pipe_bw 262144 1000
./pipe_bw 524288 1000

echo "Shared memory Latency"

./sharedmem 4 1
./sharedmem 16 1
./sharedmem 64 1
./sharedmem 256 1
./sharedmem 1024 1
./sharedmem 4096 1
./sharedmem 16384 1
./sharedmem 65536 1
./sharedmem 262144 1
./sharedmem 524288 1

