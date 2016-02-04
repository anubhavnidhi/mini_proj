make

echo "Sockets Latency"

taskset 0x1 ./socket 4 100
sleep 1m
taskset 0x1 ./socket 16 100
sleep 1m
taskset 0x1 ./socket 64 100
sleep 1m
taskset 0x1 ./socket 256 100
sleep 1m
taskset 0x1 ./socket 1024 100
sleep 1m
taskset 0x1 ./socket 4096 100
sleep 1m
taskset 0x1 ./socket 16384 100
sleep 1m
taskset 0x1 ./socket 65536 500
sleep 1m
taskset 0x1 ./socket 262144 30
sleep 1m
taskset 0x1 ./socket 524288 3

#echo "Sockets Bandwidth"

#taskset 0x1 ./socket_bw 1024 100
#taskset 0x1 ./socket_bw 4096 100
#taskset 0x1 ./socket_bw 16384 100
#taskset 0x1 ./socket_bw 65536 500
#taskset 0x1 ./socket_bw 262144 30
#taskset 0x1 ./socket_bw 524288 3
echo "\n"
echo "Pipe Latency"

<<<<<<< HEAD
taskset 0x1 ./pipe 4 100
taskset 0x1 ./pipe 16 100
taskset 0x1 ./pipe 64 100
taskset 0x1 ./pipe 256 100
taskset 0x1 ./pipe 1024 100
taskset 0x1 ./pipe 4096 100
taskset 0x1 ./pipe 16384 100
taskset 0x1 ./pipe 65536 100
taskset 0x1 ./pipe 262144 100
taskset 0x1 ./pipe 524288 100

#echo "Pipe Bandwidth"

#taskset 0x1 ./pipe_bw 1024 100
#taskset 0x1 ./pipe_bw 4096 100
#taskset 0x1 ./pipe_bw 16384 100
#taskset 0x1 ./pipe_bw 65536 100
#taskset 0x1 ./pipe_bw 262144 100
#taskset 0x1 ./pipe_bw 524288 100

#echo "Sockets Bandwidth"

#taskset 0x1 ./socket_bw 262144 30
#sleep 1m
#taskset 0x1 ./socket_bw 524288 3


#echo "Pipe Bandwidth"

#taskset 0x1 ./pipe_bw 262144 100
#taskset 0x1 ./pipe_bw 524288 100
=======
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

>>>>>>> bee1111e2932a163d19eb088f6313a5aafc6582b
