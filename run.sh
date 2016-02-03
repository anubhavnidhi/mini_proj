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
