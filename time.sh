echo $1
taskset 0x1 ./gettime $1
taskset 0x1 ./timeofday $1
taskset 0x1 ./rdtsc $1
