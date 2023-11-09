import csv
import numpy as np
import matplotlib.pyplot as plt

# Load data from CSV file
with open('time_responses_seq.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)

# Extract times and convert to numpy array
times = np.array([float(row[1]) for row in data[1:]])

# Calculate statistics
average_time = np.mean(times)
median_time = np.median(times)
variance_time = np.var(times)

print(f'Average Time: {average_time} seconds')
print(f'Median Time: {median_time} seconds')
print(f'Variance Time: {variance_time} seconds^2')

# Plot a histogram
plt.xticks(np.arange(min(times), max(times)+1, 0.5))
plt.hist(times, bins=100, edgecolor='black')
plt.title('Distribution of Execution Times')
plt.xlabel('Execution Time (seconds)')
plt.ylabel('Frequency')
plt.show()
