import numpy as np
from scipy.stats import norm
from sklearn.neighbors import KernelDensity
# Kernel Density Estimator using gaussian kernel
X = np.random.randn(100)
model = KernelDensity(kernel='gaussian',
					bandwidth=0.2)
model.fit(X[:, None])
new_data = np.linspace(-5, 5, 1000)
density = np.exp(model.score_samples(new_data[:, None]))
# print(new_data)
# Plot the densities
plt.plot(new_data, density, '-',
		color='red')
plt.xlabel('Data')
plt.ylabel('Density')
plt.title('Kernel Density Estimator using Gaussian kernel')
plt.show()
