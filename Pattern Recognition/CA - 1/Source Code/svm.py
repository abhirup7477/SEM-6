import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm

# Generate sample data
np.random.seed(0)
X = np.r_[np.random.randn(20, 2) - [2, 2], np.random.randn(20, 2) + [2, 2]]
Y = [0] * 20 + [1] * 20

# Train SVM model with RBF kernel
clf = svm.SVC(kernel='rbf', C=1.0, gamma='scale')
clf.fit(X, Y)

# Plot decision boundary
xx, yy = np.meshgrid(np.linspace(-5, 5, 50), np.linspace(-5, 5, 50))
Z = clf.decision_function(np.c_[xx.ravel(), yy.ravel()])
Z = Z.reshape(xx.shape)

plt.scatter(X[:, 0], X[:, 1], c=Y, cmap=plt.cm.Paired)
plt.contour(xx, yy, Z, levels=[0], linewidths=2, colors='k')
plt.title("SVM Decision Boundary")
plt.show()