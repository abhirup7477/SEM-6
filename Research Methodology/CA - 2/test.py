import matplotlib.pyplot as plt
# Calculate IQR
q1 = percentiles[0.25]
q3 = percentiles[0.75]
iqr = q3 - q1
print(f"Interquartile Range (IQR): {iqr}")

# Outlier detection using IQR method
lower_bound = q1 - 1.5 * iqr
upper_bound = q3 + 1.5 * iqr
outliers = df[(df[col] < lower_bound) | (df[col] > upper_bound)]
print(f"Number of outliers: {len(outliers)}")
print(f"Outliers:\n{outliers}")

# Boxplot with outlier visualization
plt.figure()
sns.boxplot(y=df[col])
plt.title(f"Boxplot of {col} with Outliers")
plt.show()