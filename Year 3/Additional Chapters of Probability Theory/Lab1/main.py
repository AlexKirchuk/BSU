"""
LABORATORY WORK: STATISTICAL GOODNESS-OF-FIT TESTS
Task 1: Normal distribution N(0, 20), n = 300
Task 2: Mixture of two Gaussian distributions
"""

import numpy as np
import pandas as pd
from scipy import stats
import matplotlib.pyplot as plt
import seaborn as sns


# =============================================================================
# TASK 1: NORMAL DISTRIBUTION
# =============================================================================

print("=" * 70)
print("TASK 1: NORMAL DISTRIBUTION N(0, 20)")
print("=" * 70)

# 1. Modeling a random sample
np.random.seed(1)
n1 = 300
mu1 = 0
sigma1 = np.sqrt(20)
sample1 = np.random.normal(loc=mu1, scale=sigma1, size=n1)

# 2. Basic descriptive statistics
mean1 = np.mean(sample1)
variance1 = np.var(sample1, ddof=1)
std_dev1 = np.std(sample1, ddof=1)
minimum1 = np.min(sample1)
maximum1 = np.max(sample1)
skewness1 = stats.skew(sample1)
kurtosis1 = stats.kurtosis(sample1, fisher=True)

stats_table1 = pd.DataFrame({
    'Statistic': ['Number of observations', 'Mean', 'Variance', 'Std. Deviation',
                  'Min', 'Max', 'Skewness', 'Kurtosis'],
    'Value': [n1, mean1, variance1, std_dev1, minimum1, maximum1, skewness1, kurtosis1]
})
print("\n--- Descriptive Statistics ---")
print(stats_table1.to_string(index=False))

# 3. Testing for normality

# Kolmogorov-Smirnov test
sample_standardized1 = (sample1 - np.mean(sample1)) / np.std(sample1, ddof=1)
ks_statistic1, ks_p_value1 = stats.kstest(sample_standardized1, 'norm')
print(f"\n--- Kolmogorov-Smirnov Test ---")
print(f"  Statistic = {ks_statistic1:.6f}, P-value = {ks_p_value1:.6f}")

# Chi-Square (Pearson) test
n_bins1 = 15
observed_freq1, bin_edges1 = np.histogram(sample1, bins=n_bins1)

cdf_values1 = stats.norm.cdf(bin_edges1, loc=np.mean(sample1), scale=np.std(sample1, ddof=1))
expected_prob1 = np.diff(cdf_values1)
expected_freq1 = expected_prob1 * n1

while np.any(expected_freq1 < 5):
    min_index1 = np.argmin(expected_freq1)
    if min_index1 < len(expected_freq1) - 1:
        expected_freq1[min_index1] += expected_freq1[min_index1 + 1]
        expected_freq1 = np.delete(expected_freq1, min_index1 + 1)
        observed_freq1[min_index1] += observed_freq1[min_index1 + 1]
        observed_freq1 = np.delete(observed_freq1, min_index1 + 1)
    else:
        expected_freq1[min_index1 - 1] += expected_freq1[min_index1]
        expected_freq1 = np.delete(expected_freq1, min_index1)
        observed_freq1[min_index1 - 1] += observed_freq1[min_index1]
        observed_freq1 = np.delete(observed_freq1, min_index1)

expected_freq1 = expected_freq1 / expected_freq1.sum() * n1

chi2_statistic1, chi2_p_value1 = stats.chisquare(observed_freq1, expected_freq1)
df1 = len(observed_freq1) - 1 - 2
chi2_p_value_manual1 = 1 - stats.chi2.cdf(chi2_statistic1, df1)

print(f"\n--- Pearson Chi-Square Test ---")
print(f"  Statistic = {chi2_statistic1:.6f}, P-value (manual) = {chi2_p_value_manual1:.6f}")
print(f"  Degrees of freedom = {df1}")

# 4. Interpretation for Task 1
alpha = 0.05
print("\n--- Interpretation ---")
print(f"  Significance level α = {alpha}")

ks_decision1 = "Fail to reject H0" if ks_p_value1 > alpha else "Reject H0"
chi2_decision1 = "Fail to reject H0" if chi2_p_value_manual1 > alpha else "Reject H0"

print(f"  K-S test: P-value = {ks_p_value1:.4f} → {ks_decision1}")
print(f"  Chi-square test: P-value = {chi2_p_value_manual1:.4f} → {chi2_decision1}")

if ks_p_value1 > alpha and chi2_p_value_manual1 > alpha:
    print("\n CONCLUSION: Data follows a normal distribution")
else:
    print("\n CONCLUSION: Data does NOT follow a normal distribution")


# =============================================================================
# TASK 2: MIXTURE OF TWO GAUSSIAN DISTRIBUTIONS
# =============================================================================

print("\n" + "=" * 70)
print("TASK 2: MIXTURE OF TWO GAUSSIAN DISTRIBUTIONS")
print("=" * 70)

# 1. Modeling a mixture of two Gaussian distributions
np.random.seed(2)
n2 = 100
mu1_2 = 0
mu2_2 = 6
sigma1_2 = 1
alpha_mix = 0.5
sigma2_2 = alpha_mix * sigma1_2
epsilon = 0.45

print("\n--- Parameters ---")
print(f"  μ1 = {mu1_2}, μ2 = {mu2_2}, σ1 = {sigma1_2}, σ2 = {sigma2_2}, ε = {epsilon}, n = {n2}")

sample2 = np.zeros(n2)
for i in range(n2):
    u = np.random.random()
    if u < epsilon:
        sample2[i] = np.random.normal(loc=mu2_2, scale=sigma2_2)
    else:
        sample2[i] = np.random.normal(loc=mu1_2, scale=sigma1_2)

# 2. Basic descriptive statistics
mean2 = np.mean(sample2)
variance2 = np.var(sample2, ddof=1)
std_dev2 = np.std(sample2, ddof=1)
minimum2 = np.min(sample2)
maximum2 = np.max(sample2)
skewness2 = stats.skew(sample2)
kurtosis2 = stats.kurtosis(sample2, fisher=True)

stats_table2 = pd.DataFrame({
    'Statistic': ['Number of observations', 'Mean', 'Variance', 'Std. Deviation',
                  'Min', 'Max', 'Skewness', 'Kurtosis'],
    'Value': [n2, mean2, variance2, std_dev2, minimum2, maximum2, skewness2, kurtosis2]
})
print("\n--- Descriptive Statistics ---")
print(stats_table2.to_string(index=False))

# 3. Testing for normality

# Kolmogorov-Smirnov test
sample_standardized2 = (sample2 - np.mean(sample2)) / np.std(sample2, ddof=1)
ks_statistic2, ks_p_value2 = stats.kstest(sample_standardized2, 'norm')
print(f"\n--- Kolmogorov-Smirnov Test ---")
print(f"  Statistic = {ks_statistic2:.6f}, P-value = {ks_p_value2:.6f}")

# Chi-Square (Pearson) test
n_bins2 = 15
observed_freq2, bin_edges2 = np.histogram(sample2, bins=n_bins2)

cdf_values2 = stats.norm.cdf(bin_edges2, loc=np.mean(sample2), scale=np.std(sample2, ddof=1))
expected_prob2 = np.diff(cdf_values2)
expected_freq2 = expected_prob2 * n2

while np.any(expected_freq2 < 5):
    min_index2 = np.argmin(expected_freq2)
    if min_index2 < len(expected_freq2) - 1:
        expected_freq2[min_index2] += expected_freq2[min_index2 + 1]
        expected_freq2 = np.delete(expected_freq2, min_index2 + 1)
        observed_freq2[min_index2] += observed_freq2[min_index2 + 1]
        observed_freq2 = np.delete(observed_freq2, min_index2 + 1)
    else:
        expected_freq2[min_index2 - 1] += expected_freq2[min_index2]
        expected_freq2 = np.delete(expected_freq2, min_index2)
        observed_freq2[min_index2 - 1] += observed_freq2[min_index2]
        observed_freq2 = np.delete(observed_freq2, min_index2)

expected_freq2 = expected_freq2 / expected_freq2.sum() * n2

chi2_statistic2, chi2_p_value2 = stats.chisquare(observed_freq2, expected_freq2)
df2 = len(observed_freq2) - 1 - 2
chi2_p_value_manual2 = 1 - stats.chi2.cdf(chi2_statistic2, df2)

print(f"\n--- Pearson Chi-Square Test ---")
print(f"  Statistic = {chi2_statistic2:.6f}, P-value (manual) = {chi2_p_value_manual2:.6f}")
print(f"  Degrees of freedom = {df2}")

# 4. Interpretation for Task 2
print("\n--- Interpretation ---")
print(f"  Significance level α = {alpha}")

ks_decision2 = "Fail to reject H0" if ks_p_value2 > alpha else "Reject H0"
chi2_decision2 = "Fail to reject H0" if chi2_p_value_manual2 > alpha else "Reject H0"

print(f"  K-S test: P-value = {ks_p_value2:.4f} → {ks_decision2}")
print(f"  Chi-square test: P-value = {chi2_p_value_manual2:.4f} → {chi2_decision2}")

if ks_p_value2 > alpha and chi2_p_value_manual2 > alpha:
    print("\n CONCLUSION: Data follows a normal distribution")
    print("  (This is interesting because the data is actually a mixture!)")
else:
    print("\n CONCLUSION: Data does NOT follow a normal distribution")
    print("  (This is expected since the data is a mixture of two Gaussians)")


# =============================================================================
# GRAPHICAL ANALYSIS FOR TASK 2
# =============================================================================

print("\n--- Graphical Analysis ---")

plt.figure(figsize=(10, 6))

sns.histplot(sample2, kde=False, stat='density', bins=15,
             color='skyblue', edgecolor='black', alpha=0.7)

x_range = np.linspace(min(sample2) - 1, max(sample2) + 1, 1000)

plt.plot(x_range, stats.norm.pdf(x_range, loc=mean2, scale=std_dev2),
         'r-', linewidth=2.5, label='Normal PDF (fitted)')

def mixture_pdf(x, mu1, mu2, sigma1, sigma2, eps):
    return (1 - eps) * stats.norm.pdf(x, loc=mu1, scale=sigma1) + \
           eps * stats.norm.pdf(x, loc=mu2, scale=sigma2)

plt.plot(x_range, mixture_pdf(x_range, mu1_2, mu2_2, sigma1_2, sigma2_2, epsilon),
         'g--', linewidth=2.5, label='True mixture PDF')

plt.title('Task 2: Mixture of Two Gaussian Distributions', fontsize=14, fontweight='bold')
plt.xlabel('Value')
plt.ylabel('Density')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('task2_histogram.png', dpi=150, bbox_inches='tight')
plt.show()

print("Graphical analysis complete. See 'task2_histogram.png'")


# =============================================================================
# COMPARATIVE SUMMARY
# =============================================================================

print("\n" + "=" * 70)
print("COMPARATIVE SUMMARY")
print("=" * 70)

comparison_data = {
    'Task': ['Task 1: Normal', 'Task 2: Mixture'],
    'Distribution Type': ['Single Gaussian', 'Mixture of 2 Gaussians'],
    'n': [n1, n2],
    'Mean': [f"{mean1:.3f}", f"{mean2:.3f}"],
    'Variance': [f"{variance1:.3f}", f"{variance2:.3f}"],
    'Skewness': [f"{skewness1:.3f}", f"{skewness2:.3f}"],
    'Kurtosis': [f"{kurtosis1:.3f}", f"{kurtosis2:.3f}"],
    'K-S P-value': [f"{ks_p_value1:.4f}", f"{ks_p_value2:.4f}"],
    'χ² P-value': [f"{chi2_p_value_manual1:.4f}", f"{chi2_p_value_manual2:.4f}"],
    'Normality': ['Yes' if ks_p_value1 > alpha and chi2_p_value_manual1 > alpha else 'No',
                   'Yes' if ks_p_value2 > alpha and chi2_p_value_manual2 > alpha else 'No']
}

comparison_df = pd.DataFrame(comparison_data)
print("\n", comparison_df.to_string(index=False))

print("\n" + "=" * 70)
print("END OF ANALYSIS")
print("=" * 70)
