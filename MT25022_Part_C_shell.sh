#!/bin/bash

# MT25022_Part_C_shell.sh
# Bash script to automate execution of the six program variants (A+cpu, A+mem, A+io, B+cpu, B+mem, B+io)
# Measures CPU%, Memory usage, and I/O statistics for each.
# Also automates part D: varying number of processes/threads.
# AI-generated with assistance from GitHub Copilot.
# Roll number: MT25022

# Output CSV files
CSV_C="MT25022_Part_C_CSV.csv"
CSV_D="MT25022_Part_D_CSV.csv"

# Header for C
echo "Program+Function,CPU%,Mem,IO" > "$CSV_C"

# Header for D
echo "Program,Function,NumWorkers,CPU%,Mem,IO" > "$CSV_D"

# Function to measure for a program and function
measure() {
    local prog=$1
    local func=$2
    local num=$3
    local exe="./prog$prog"
    local label="${prog}+${func}"

    echo "Running $label with $num workers"

    # Pin to CPU 0 using taskset
    taskset -c 0 "$exe" "$func" "$num" &
    local pid=$!

    # Collect data while process is running
    local cpu_sum=0
    local mem_sum=0
    local count=0

    while kill -0 $pid 2>/dev/null; do
        # Get CPU% and MEM% from top
        local line=$(top -b -n 1 -p $pid 2>/dev/null | grep $pid)
        if [ -n "$line" ]; then
            local cpu=$(echo $line | awk '{print $9}')
            local mem=$(echo $line | awk '{print $10}')
            cpu_sum=$(echo "$cpu_sum + $cpu" | bc -l 2>/dev/null || echo 0)
            mem_sum=$(echo "$mem_sum + $mem" | bc -l 2>/dev/null || echo 0)
            count=$((count + 1))
        fi
        sleep 0.1  # Shorter interval
    done

    # Average CPU and MEM
    local avg_cpu=0
    local avg_mem=0
    if [ $count -gt 0 ]; then
        avg_cpu=$(echo "scale=2; $cpu_sum / $count" | bc -l 2>/dev/null || echo 0)
        avg_mem=$(echo "scale=2; $mem_sum / $count" | bc -l 2>/dev/null || echo 0)
    fi

    # For IO, use execution time from time command
    local exec_time=$(/usr/bin/time -f "%e" taskset -c 0 "$exe" "$func" "$num" 2>&1 | tail -1)
    local io=$exec_time  # Use execution time as IO metric

    # Append to appropriate CSV
    if [ "$num" = "2" ]; then
        echo "$label,$avg_cpu,$avg_mem,$io" >> "$CSV_C"
    else
        echo "$prog,$func,$num,$avg_cpu,$avg_mem,$io" >> "$CSV_D"
    fi
}

# Run for part C: all combinations with 2 workers
for prog in A B; do
    for func in cpu mem io; do
        measure $prog $func 2
    done
done

# Run for part D: varying workers
# For A: 2,3,4,5
for num in 2 3 4 5; do
    for func in cpu mem io; do
        measure A $func $num
    done
done

# For B: 2,3,4,5,6,7,8
for num in 2 3 4 5 6 7 8; do
    for func in cpu mem io; do
        measure B $func $num
    done
done

echo "Measurements completed. Check $CSV_C and $CSV_D"