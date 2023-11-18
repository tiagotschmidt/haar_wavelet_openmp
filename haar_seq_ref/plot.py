import csv
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

# Load data from CSV file
with open('time_responses_seq.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)

# Extract times and convert to numpy array
times = np.array([float(row[1]) for row in data[1:]])

mu, std = norm.fit(times)

# Plot histogram
plt.hist(times, bins=25, density=True, alpha=0.6, color=f'C0', label=f'Sequencial')

# Plot fitted Gaussian curve
xmin, xmax = plt.xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)
plt.plot(x, p, f'C0', linewidth=2)

# Display statistics
avg = np.mean(times)
median = np.median(times)
stdev = np.std(times)
plt.title(f'Elapsed Times - Sequencial\nAverage: {avg:.2f}, Median: {median:.2f}, StdDev: {stdev:.2f}')
plt.xlabel('Elapsed Time (seconds)')
plt.ylabel('Frequency')
plt.legend()
plt.show()

