import csv
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

# Function to read elapsed times from a CSV file
def read_elapsed_times(file_path):
    with open(file_path, 'r') as csvfile:
        times = [float(row[0]) for row in csv.reader(csvfile)]
    return times

# File paths for your CSV files
file_paths = ['Pré-haar_times.csv', 'Pós-haar_times.csv', 'Pós-haar_times.csv']

# Plot Gaussian graphics separately
for i, file_path in enumerate(file_paths, start=1):
    # Read elapsed times from CSV file
    times = read_elapsed_times(file_path)

    # Fit Gaussian distribution parameters
    mu, std = norm.fit(times)

    # Plot histogram
    plt.hist(times, bins=25, density=False, alpha=0.6, color=f'C{i-1}', label=f'{file_path}')

    # Plot fitted Gaussian curve
    xmin, xmax = plt.xlim()
    x = np.linspace(xmin, xmax, 100)
    p = norm.pdf(x, mu, std)
    plt.plot(x, p, f'C{i-1}', linewidth=2)

    # Display statistics
    avg = np.mean(times)
    median = np.median(times)
    stdev = np.std(times)

    plt.title(f'Elapsed Times - {file_path}\nAverage: {avg:.2f}, Median: {median:.2f}, StdDev: {stdev:.2f}')
    plt.xlabel('Elapsed Time (seconds)')
    plt.ylabel('Frequency')
    plt.legend()
    plt.show()
