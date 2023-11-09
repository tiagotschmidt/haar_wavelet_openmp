#!/bin/bash

# Number of repetitions
repetitions=100

# Output file for time responses in CSV format
output_file="time_responses_parallel_gpt.csv"

# Compile your C code
make all

# Clear existing output file
> $output_file

# Run the experiment 100 times
for ((i=1; i<=$repetitions; i++))
do
    echo "Running experiment $i..."
    
    # Record the start time
    start_time=$(date +%s.%N)

    # Run your parallel code
    make run

    # Record the end time
    end_time=$(date +%s.%N)

    # Calculate the elapsed time
    elapsed_time=$(echo "$end_time - $start_time" | bc)

    # Append the result to the output file in CSV format
    echo "$i,$elapsed_time" >> $output_file
done

echo "Experiment completed. Time responses saved to $output_file"
