# KNN Density esitmator
gaussian = norm(loc=0.5, scale=0.2)
X = gaussian.rvs(500)
grid = np.linspace(-0.1, 1.1, 1000)
k_set = [5, 10, 20]
fig, axes = plt.subplots(3, 1, figsize=(10, 10))
for i, ax in enumerate(axes.flat):
	K = k_set[i]
	p = np.zeros_like(grid)
	n = X.shape[0]
	for i, x in enumerate(grid):
		dists = np.abs(X-x)
		neighbours = dists.argsort()
		neighbour_K = neighbours[K]
		p[i] = (K/n) * 1/(2 * dists[neighbour_K])
	ax.plot(grid, p, color='orange')
	ax.set_title(f'$k={K}$')
plt.show()
