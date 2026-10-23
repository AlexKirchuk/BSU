import math
import random
import matplotlib.pyplot as plt


# =============================================================================
# PART 1: GENERATION
# =============================================================================

def generate_normal_box_muller(mu, sigma, n):
    """Generate n samples from N(mu, sigma^2) using Box-Muller method"""
    result = []
    for i in range(0, n, 2):
        u1 = random.random()
        u2 = random.random()
        z1 = math.sqrt(-2.0 * math.log(u1)) * math.cos(2.0 * math.pi * u2)
        z2 = math.sqrt(-2.0 * math.log(u1)) * math.sin(2.0 * math.pi * u2)
        result.append(mu + sigma * z1)
        if len(result) < n:
            result.append(mu + sigma * z2)
    return result


def generate_mixture(n, mu1, sigma1, mu2, sigma2, epsilon):
    """Generate n samples from mixture of two Gaussians"""
    sample = []
    for _ in range(n):
        u = random.random()
        if u < epsilon:
            sample.append(generate_normal_box_muller(mu2, sigma2, 1)[0])
        else:
            sample.append(generate_normal_box_muller(mu1, sigma1, 1)[0])
    return sample


# =============================================================================
# PART 2: DESCRIPTIVE STATISTICS
# =============================================================================

def compute_mean(data):
    return sum(data) / len(data)


def compute_variance(data, mean, ddof=1):
    total = sum((x - mean) ** 2 for x in data)
    return total / (len(data) - ddof)


def compute_std_dev(variance):
    return math.sqrt(variance)


def compute_min_max(data):
    return min(data), max(data)


def compute_skewness(data, mean, std):
    n = len(data)
    return sum(((x - mean) / std) ** 3 for x in data) / n


def compute_kurtosis(data, mean, std):
    n = len(data)
    return sum(((x - mean) / std) ** 4 for x in data) / n - 3.0


# =============================================================================
# PART 3: NORMAL CDF (using error function)
# =============================================================================

def normal_cdf(x, mu, sigma):
    """Standard normal CDF using error function"""
    return 0.5 * (1.0 + math.erf((x - mu) / (sigma * math.sqrt(2.0))))


# =============================================================================
# PART 4: KOLMOGOROV-SMIRNOV TEST
# =============================================================================

def ks_p_value_approx(d, n):
    """Approximate p-value for Kolmogorov-Smirnov test"""
    x = math.sqrt(n) * d
    sum_val = 0.0
    for k in range(1, 11):
        sign = 1.0 if k % 2 == 1 else -1.0
        term = sign * math.exp(-2.0 * k * k * x * x)
        sum_val += term
    p_value = 1.0 - (1.0 - 2.0 * sum_val)
    return max(0.0, min(1.0, p_value))


def ks_test(data, mu, sigma):
    """Kolmogorov-Smirnov test for normality"""
    n = len(data)
    sorted_data = sorted(data)
    d_max = 0.0
    for i, x in enumerate(sorted_data):
        f_emp = (i + 1) / n
        f_theo = normal_cdf(x, mu, sigma)
        d_max = max(d_max, abs(f_emp - f_theo))
    p_value = ks_p_value_approx(d_max, n)
    return d_max, p_value


# =============================================================================
# PART 5: CHI-SQUARE TEST
# =============================================================================

def chi2_cdf(x, df):
    """
    Chi-square CDF using incomplete gamma function
    We use scipy.special.gammainc since pure Python implementation
    would be extremely complex (numerical integration)
    """
    from scipy.special import gammainc
    return gammainc(df / 2.0, x / 2.0)


def chi_square_test(data, mu, sigma, n_bins=15):
    """Pearson's chi-square test for normality"""
    n = len(data)
    min_val = min(data)
    max_val = max(data)
    pad = (max_val - min_val) * 0.05
    left = min_val - pad
    right = max_val + pad
    bin_width = (right - left) / n_bins
    bin_edges = [left + i * bin_width for i in range(n_bins + 1)]

    # Observed frequencies
    observed = [0] * n_bins
    for x in data:
        for i in range(n_bins):
            if bin_edges[i] <= x < bin_edges[i + 1]:
                observed[i] += 1
                break
        if x == bin_edges[-1]:
            observed[-1] += 1

    # Expected frequencies
    expected = [0.0] * n_bins
    for i in range(n_bins):
        prob = normal_cdf(bin_edges[i + 1], mu, sigma) - normal_cdf(bin_edges[i], mu, sigma)
        expected[i] = prob * n

    # Combine small bins (expected < 5)
    obs = observed[:]
    exp = expected[:]

    while True:
        min_exp = min(exp)
        if min_exp >= 5.0:
            break
        min_idx = exp.index(min_exp)
        if min_idx == len(exp) - 1:
            exp[min_idx - 1] += exp[min_idx]
            obs[min_idx - 1] += obs[min_idx]
            del exp[min_idx]
            del obs[min_idx]
        else:
            exp[min_idx] += exp[min_idx + 1]
            obs[min_idx] += obs[min_idx + 1]
            del exp[min_idx + 1]
            del obs[min_idx + 1]

    # Normalize expected frequencies to sum to n
    sum_exp = sum(exp)
    exp = [e / sum_exp * n for e in exp]

    # Chi-square statistic
    chi2_stat = sum((o - e) ** 2 / e for o, e in zip(obs, exp))

    # Degrees of freedom: k - 1 - 2 (estimated parameters: mean and variance)
    k = len(obs)
    df = k - 1 - 2
    p_value = 1.0 - chi2_cdf(chi2_stat, df)

    return chi2_stat, p_value, df


# =============================================================================
# PART 6: MIXTURE PDF
# =============================================================================

def normal_pdf(x, mu, sigma):
    """Probability density function of normal distribution"""
    return (1.0 / (sigma * math.sqrt(2.0 * math.pi))) * math.exp(-((x - mu) ** 2) / (2.0 * sigma * sigma))


def mixture_pdf(x, mu1, sigma1, mu2, sigma2, epsilon):
    """Probability density function of mixture of two Gaussians"""
    return (1.0 - epsilon) * normal_pdf(x, mu1, sigma1) + epsilon * normal_pdf(x, mu2, sigma2)


# =============================================================================
# PART 7: HISTOGRAM (manual)
# =============================================================================

def compute_histogram(data, n_bins=15):
    """Compute histogram bins and frequencies manually"""
    min_val = min(data)
    max_val = max(data)
    pad = (max_val - min_val) * 0.05
    left = min_val - pad
    right = max_val + pad
    bin_width = (right - left) / n_bins
    bin_edges = [left + i * bin_width for i in range(n_bins + 1)]

    frequencies = [0] * n_bins
    for x in data:
        for i in range(n_bins):
            if bin_edges[i] <= x < bin_edges[i + 1]:
                frequencies[i] += 1
                break
        if x == bin_edges[-1]:
            frequencies[-1] += 1

    return frequencies, bin_edges, bin_width


# =============================================================================
# PART 8: MAIN PROGRAM
# =============================================================================

def main():
    random.seed(1)

    # Task 2 parameters
    print("=" * 70)
    print("TASK 2: MIXTURE OF TWO GAUSSIAN DISTRIBUTIONS")
    print("=" * 70)

    n = 100
    mu1 = 0.0
    sigma1 = 1.0
    mu2 = 6.0
    alpha = 0.5
    sigma2 = alpha * sigma1
    epsilon = 0.45

    print("\n--- Parameters ---")
    print(f"  mu1 = {mu1}, mu2 = {mu2}, sigma1 = {sigma1}, sigma2 = {sigma2}")
    print(f"  epsilon = {epsilon}, n = {n}")

    # 1. Generate mixture
    sample = generate_mixture(n, mu1, sigma1, mu2, sigma2, epsilon)

    # 2. Descriptive statistics
    mean = compute_mean(sample)
    variance = compute_variance(sample, mean)
    std = compute_std_dev(variance)
    min_val, max_val = compute_min_max(sample)
    skewness = compute_skewness(sample, mean, std)
    kurtosis = compute_kurtosis(sample, mean, std)

    print("\n--- Descriptive Statistics ---")
    print(f"  Number of observations: {n}")
    print(f"  Mean: {mean:.6f}")
    print(f"  Variance: {variance:.6f}")
    print(f"  Std. Deviation: {std:.6f}")
    print(f"  Min: {min_val:.6f}")
    print(f"  Max: {max_val:.6f}")
    print(f"  Skewness: {skewness:.6f}")
    print(f"  Kurtosis: {kurtosis:.6f}")

    # 3. Kolmogorov-Smirnov test
    ks_stat, ks_p = ks_test(sample, mean, std)
    print("\n--- Kolmogorov-Smirnov Test ---")
    print(f"  D statistic: {ks_stat:.6f}")
    print(f"  P-value: {ks_p:.6f}")

    # 4. Chi-square test
    chi2_stat, chi2_p, df = chi_square_test(sample, mean, std, n_bins=15)
    print("\n--- Pearson Chi-Square Test ---")
    print(f"  Chi-square statistic: {chi2_stat:.6f}")
    print(f"  Degrees of freedom: {df}")
    print(f"  P-value: {chi2_p:.6f}")

    # 5. Interpretation
    alpha_level = 0.05
    print("\n--- Interpretation ---")
    print(f"  Significance level alpha = {alpha_level}")

    if ks_p > alpha_level:
        print(f"  K-S test: P-value = {ks_p:.4f} > {alpha_level} -> Fail to reject H0")
    else:
        print(f"  K-S test: P-value = {ks_p:.4f} <= {alpha_level} -> Reject H0")

    if chi2_p > alpha_level:
        print(f"  Chi-square test: P-value = {chi2_p:.4f} > {alpha_level} -> Fail to reject H0")
    else:
        print(f"  Chi-square test: P-value = {chi2_p:.4f} <= {alpha_level} -> Reject H0")

    if ks_p > alpha_level and chi2_p > alpha_level:
        print("\n  CONCLUSION: Data follows a normal distribution")
    else:
        print("\n  CONCLUSION: Data does NOT follow a normal distribution")
        print("  (Expected: mixture of two Gaussians)")

    # 6. Graphical analysis (manual histogram)
    print("\n--- Graphical Analysis ---")

    n_bins = 15
    frequencies, bin_edges, bin_width = compute_histogram(sample, n_bins)

    # Convert frequencies to density (area = 1)
    density = [f / (n * bin_width) for f in frequencies]

    # Bin centers for plotting
    bin_centers = [(bin_edges[i] + bin_edges[i + 1]) / 2.0 for i in range(n_bins)]

    # Create figure
    plt.figure(figsize=(10, 6))

    # Plot histogram (bar chart)
    bars = plt.bar(bin_centers, density, width=bin_width * 0.9,
                   color='skyblue', edgecolor='black', alpha=0.7,
                   label='Histogram')

    # Plot fitted normal PDF
    x_range = [min_val - 1 + i * 0.01 for i in range(int((max_val - min_val + 2) * 100))]
    fitted_pdf = [normal_pdf(x, mean, std) for x in x_range]
    plt.plot(x_range, fitted_pdf, 'r-', linewidth=2.5, label='Normal PDF (fitted)')

    # Plot true mixture PDF
    true_pdf = [mixture_pdf(x, mu1, sigma1, mu2, sigma2, epsilon) for x in x_range]
    plt.plot(x_range, true_pdf, 'g--', linewidth=2.5, label='True mixture PDF')

    plt.title('Mixture of Two Gaussian Distributions', fontsize=14, fontweight='bold')
    plt.xlabel('Value')
    plt.ylabel('Density')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig('task2_manual_histogram.png', dpi=150, bbox_inches='tight')
    plt.show()

    print("  Graphical analysis complete. See 'task2_manual_histogram.png'")


if __name__ == "__main__":
    main()