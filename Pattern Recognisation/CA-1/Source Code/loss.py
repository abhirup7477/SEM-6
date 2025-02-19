import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm

# Generate Noisy Data
np.random.seed(42)
x = np.linspace(0, 10, 100)  # X values from 0 to 10
y = np.sin(x) + np.random.normal(0, 0.3, size=len(x))  # Add noise to sine function

# Apply LOESS Smoothing
lowess = sm.nonparametric.lowess(y, x, frac=0.2)  # frac controls smoothness

# Extract smoothed values
x_smooth, y_smooth = lowess[:, 0], lowess[:, 1]

# Plot Original Noisy Data
plt.scatter(x, y, label="Noisy Data", color="gray", alpha=0.5)

# Plot LOESS Smoothed Curve
plt.plot(x_smooth, y_smooth, label="LOESS Smoothed Curve", color="red", linewidth=2)

# Labels and Title
plt.xlabel("X values")
plt.ylabel("Y values")
plt.title("LOESS Smoothing on Noisy Data")
plt.legend()
plt.show()