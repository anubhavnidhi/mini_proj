make


echo "Pipe Latency"

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


echo "Shared memory Latency"

taskset 0x1 ./sharedmem 4 100
taskset 0x1 ./sharedmem 16 100
taskset 0x1 ./sharedmem 64 100
taskset 0x1 ./sharedmem 256 100
taskset 0x1 ./sharedmem 1024 100
taskset 0x1 ./sharedmem 4096 100
taskset 0x1 ./sharedmem 16384 100
taskset 0x1 ./sharedmem 65536 100
taskset 0x1 ./sharedmem 262144 100
taskset 0x1 ./sharedmem 524288 100


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
taskset 0x1 ./socket 65536 10
sleep 1m
taskset 0x1 ./socket 262144 10
sleep 1m
taskset 0x1 ./socket 524288 5
