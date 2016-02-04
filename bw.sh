
echo "Sockets BW"

taskset 0x1 ./socket_bw 1000000 1
sleep 1m
taskset 0x1 ./socket_bw 1000000 2
sleep 1m
taskset 0x1 ./socket_bw 1000000 3
sleep 1m
taskset 0x1 ./socket_bw 1000000 4
sleep 1m
taskset 0x1 ./socket_bw 1000000 5
sleep 1m
taskset 0x1 ./socket_bw 1000000 6
sleep 1m
taskset 0x1 ./socket_bw 1000000 7
sleep 1m
taskset 0x1 ./socket_bw 1000000 8
sleep 1m
taskset 0x1 ./socket_bw 1000000 9
sleep 1m
taskset 0x1 ./socket_bw 1000000 10