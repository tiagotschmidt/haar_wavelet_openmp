#!/bin/bash

# Run the C program 100 times and save elapsed time values to CSV files
for i in {1..100}; do
    echo "Running iteration $i"
    output=$(make run)  # Replace with the actual name of your compiled C program

    # Extract labels and elapsed times
    label=$(echo "$output" | grep "Label:" | awk '{print $2}')
    elapsed_time=$(echo "$output" | grep "Elapsed Time:" | awk '{print $3}')

    # Save elapsed time to a CSV file
    echo $elapsed_time >> "${label}_times.csv"

    label=$(echo "$output" | grep "Label1:" | awk '{print $2}')
    elapsed_time=$(echo "$output" | grep "Elapsed Time1:" | awk '{print $3}')

    # Save elapsed time to a CSV file
    echo $elapsed_time >> "${label}_times.csv"

    label=$(echo "$output" | grep "Label2:" | awk '{print $2}')
    elapsed_time=$(echo "$output" | grep "Elapsed Time2:" | awk '{print $3}')

    # Save elapsed time to a CSV file
    echo $elapsed_time >> "${label}_times.csv"
done

echo "Experiments completed. Elapsed times saved to CSV files."
