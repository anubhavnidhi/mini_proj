
echo "Pipe BW"

taskset 0x1 ./pipe_bw 100000 10
taskset 0x1 ./pipe_bw 200000 10
taskset 0x1 ./pipe_bw 300000 10
taskset 0x1 ./pipe_bw 400000 10
taskset 0x1 ./pipe_bw 500000 10
taskset 0x1 ./pipe_bw 600000 10
taskset 0x1 ./pipe_bw 700000 10
taskset 0x1 ./pipe_bw 800000 10
taskset 0x1 ./pipe_bw 900000 10
taskset 0x1 ./pipe_bw 1000000 10

echo "Socket BW"

taskset 0x1 ./socket_bw 100000 10
sleep 1m
taskset 0x1 ./socket_bw 200000 10
sleep 1m
taskset 0x1 ./socket_bw 300000 10
sleep 1m
taskset 0x1 ./socket_bw 400000 10
sleep 1m
taskset 0x1 ./socket_bw 500000 10
sleep 1m
taskset 0x1 ./socket_bw 600000 10
sleep 1m
taskset 0x1 ./socket_bw 700000 10
sleep 1m
taskset 0x1 ./socket_bw 800000 10
sleep 1m
taskset 0x1 ./socket_bw 900000 10
sleep 1m
taskset 0x1 ./socket_bw 1000000 10