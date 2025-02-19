import numpy as np

def hist_pdf(x, data, n_bins=2,
			minv=None, maxv=None):
	if minv is None:
		minv = np.min(data)
	if maxv is None:
		maxv = np.max(data)
	d = (maxv-minv) / n_bins
	bins = np.arange(minv, maxv, d)
	bin_id = int((x-minv)/d)
	bin_minv = minv+d*bin_id
	bin_maxv = minv+d*(bin_id+1)
	n_data = len(data)
	y = len(data[np.where((data > bin_minv)\
						& (data < bin_maxv))])
	pdf = (1.0/d) * (y / n_data)
	return pdf

from sklearn.datasets import load_boston
import matplotlib.pyplot as plt
ds = load_boston()
data = ds['target']
# Demo histogram
xvals = np.arange(min(data), max(data), 1)
n_bins = 15
pdf = [hist_pdf(x, data, n_bins=n_bins) for x in xvals]
plt.xlabel('Data')
plt.ylabel('Density')
plt.title('Histogram Density Estimation')
plt.plot(xvals, pdf)
plt.show()
