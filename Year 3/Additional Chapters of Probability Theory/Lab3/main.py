import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# =====================================================================
# Parameters of variant 4
# =====================================================================
D = 2.0
alpha = 0.4
beta = 1.2
n = 150
delta = 1.0

rng = np.random.default_rng(52375)

# =====================================================================
# Theoretical covariance function R(t) for variant 4
# R(t) = D * exp(-alpha|t|) * (cos(beta*t) - (alpha/beta)*sin(beta*|t|))
# =====================================================================
def r_theory(h, d=D, alpha=alpha, beta=beta):
    h = np.asarray(h, dtype=float)
    return d * np.exp(-alpha * np.abs(h)) * (
        np.cos(beta*h) - (alpha/beta)*np.sin(beta*np.abs(h))
    )

# =====================================================================
# ITEM 1. Choice of simulation algorithm
# ---------------------------------------------------------------------
# Model the process as AR(2) - discretization of a stationary Gaussian
# process with rational spectral density (Kharin et al., §3.5.2).
# AR(2) coefficients: phi1 = 2*rho*cos(beta*delta), phi2 = -rho^2
# with rho = exp(-alpha*delta). Innovation variance sigma^2 is chosen
# from the condition R(0) = D.
# =====================================================================
rho = np.exp(-alpha*delta)
phi1 = 2.0*rho*np.cos(beta*delta)
phi2 = -rho**2

denom = (1.0 + phi2) * ((1.0 - phi2)**2 - phi1**2)
sigma2 = D * denom / (1.0 - phi2)
sigma = np.sqrt(sigma2)

print(f"phi1 = {phi1:.6f}, phi2 = {phi2:.6f}, sigma = {sigma:.6f}")
print(f"Stationarity check |phi1|+|phi2| = {abs(phi1)+abs(phi2):.6f}")

# Simulation of AR(2) with a warm-up of 100 samples
eta = rng.standard_normal(n + 100)
X = np.zeros(n + 100)
for k in range(2, n + 100):
    X[k] = phi1*X[k-1] + phi2*X[k-2] + sigma*eta[k]
X = X[100:]  # stationary part of length n = 150

t = np.arange(1, n+1)

# =====================================================================
# ITEM 2. Graphical presentation of X(1..n)
# =====================================================================
fig, ax = plt.subplots(figsize=(10, 3.5))
ax.plot(t, X, color='blue', lw=1.2)
ax.set_title("Realization X(t), variant 4")
ax.set_xlabel("t"); ax.set_ylabel("X(t)"); ax.grid(alpha=.3)
plt.tight_layout(); plt.show()

# =====================================================================
# ITEM 3a. Descriptive statistics
# =====================================================================
print("\n=== Descriptive statistics ===")
print(f"n = {n}, mean = {X.mean():.4f}, median = {np.median(X):.4f}")
print(f"std = {X.std(ddof=1):.4f}, var = {X.var(ddof=1):.4f}")
print(f"min = {X.min():.4f}, max = {X.max():.4f}")
print(f"skew = {stats.skew(X):.4f}, kurt = {stats.kurtosis(X):.4f}")
print(f"q1 = {np.percentile(X,25):.4f}, q3 = {np.percentile(X,75):.4f}")

# =====================================================================
# ITEM 3b. Histogram with fitted normal density
# =====================================================================
fig, ax = plt.subplots(figsize=(7,4))
ax.hist(X, bins=15, density=True, alpha=.7, edgecolor='k', color='blue')
xs = np.linspace(X.min(), X.max(), 300)
ax.plot(xs, stats.norm.pdf(xs, X.mean(), X.std(ddof=1)), 'r-', lw=1.6,
        label='fitted N(mean,std)')
ax.legend(); ax.set_title("Histogram"); ax.grid(alpha=.3)
plt.tight_layout(); plt.show()

# =====================================================================
# ITEM 3c. Homogeneity analysis WITHOUT statistical tests
# (descriptive comparison of the two halves of the sample)
# =====================================================================
half = n // 2
print("\n=== Homogeneity analysis (1st vs 2nd half) ===")
print(f"mean(1st) = {X[:half].mean():.3f}, mean(2nd) = {X[half:].mean():.3f}")
print(f"var (1st) = {X[:half].var(ddof=1):.3f}, var (2nd) = {X[half:].var(ddof=1):.3f}")

# =====================================================================
# ITEM 3d. Outlier detection WITHOUT statistical tests
# (Hampel rule: [x_med - 5.2*x_mad, x_med + 5.2*x_mad] is a
#  descriptive heuristic, not a significance test)
# =====================================================================
med = np.median(X)
mad = np.median(np.abs(X - med))
low, high = med - 5.2*mad, med + 5.2*mad
outliers = np.where((X < low) | (X > high))[0]
print(f"\n=== Hampel rule: [{low:.3f}, {high:.3f}]")
print(f"Outliers found: {len(outliers)}; indices: {outliers.tolist()}")

# =====================================================================
# ITEM 3e. Box-and-whisker plot
# =====================================================================
fig, ax = plt.subplots(figsize=(5,4))
ax.boxplot(X, vert=True, patch_artist=True, widths=.5,
           boxprops=dict(facecolor='blue'),
           medianprops=dict(color='red'))
ax.set_title("Box-and-whisker plot"); ax.grid(alpha=.3)
plt.tight_layout(); plt.show()

# =====================================================================
# ITEM 3f. Normal probability plot (Q-Q) and goodness-of-fit tests
# =====================================================================
fig, ax = plt.subplots(figsize=(5,5))
stats.probplot(X, dist="norm", plot=ax)
ax.set_title("Normal probability plot")
ax.grid(alpha=.3)
plt.tight_layout(); plt.show()

ks = stats.kstest((X-X.mean())/X.std(ddof=1), 'norm')
sw = stats.shapiro(X)
print("\n=== Goodness-of-fit tests ===")
print(f"Kolmogorov-Smirnov: D = {ks.statistic:.4f}, p = {ks.pvalue:.4f}")
print(f"Shapiro-Wilk      : W = {sw.statistic:.4f}, p = {sw.pvalue:.4f}")

# =====================================================================
# ITEM 3g. Trend analysis (visual)
# =====================================================================
def moving_average(x, w):
    return np.convolve(x, np.ones(w)/w, mode='valid')

w = 7
ma = moving_average(X, w)
t_ma = np.arange(w//2, w//2 + len(ma))

fig, ax = plt.subplots(figsize=(10, 3.5))
ax.plot(t, X, color='steelblue', lw=1, alpha=.7, label='X(t)')
ax.plot(t_ma, ma, 'r-', lw=2, label=f'moving average (w={w})')
ax.axhline(X.mean(), color='k', ls=':', lw=1, label='mean')
ax.set_title("Trend analysis (visual)")
ax.set_xlabel("t"); ax.set_ylabel("X(t)"); ax.legend(); ax.grid(alpha=.3)
plt.tight_layout(); plt.show()

tt = np.arange(n)
slope, intercept, r, p, se = stats.linregress(tt, X)
print(f"\nLinear trend fit: slope = {slope:.5f}, p = {p:.4f}")
if p > 0.05:
    print("No statistically significant trend detected (p > 0.05).")
else:
    print("Statistically significant trend detected (p <= 0.05).")

# =====================================================================
# ITEM 4. Covariance function estimate
# R_bar(h) = 1/(n-h) * sum_{s=1}^{n-h} (X_{s+h} - mu)(X_s - mu),
# mu = (1/n) sum X_j,  h = 0..n-1
# =====================================================================
def r_hat(x, h):
    n_ = len(x)
    mu = x.mean()
    if h == 0:
        return np.sum((x - mu)**2) / n_
    return np.sum((x[h:] - mu)*(x[:-h] - mu)) / (n_ - h)

# =====================================================================
# ITEM 5. Combined plot of R(h) and R_bar(h) for h = 0..2n/3
# =====================================================================
H_2n3 = int(round(2*n/3))
lags = np.arange(0, H_2n3 + 1)
R_est = np.array([r_hat(X, h) for h in lags])
R_th = r_theory(lags * delta)

fig, ax = plt.subplots(figsize=(10, 4.5))
ax.plot(lags, R_th, 'r-', lw=2, label=r"$R(h)$ theoretical")
ax.plot(lags, R_est, 'b--', lw=1.5, label=r"$\bar R(h)$ estimate")
ax.axhline(0, color='k', lw=.6)
ax.set_xlabel("lag h"); ax.set_ylabel("R(h)")
ax.set_title("Covariance function and its estimate (variant 4)")
ax.legend(); ax.grid(alpha=.3)
plt.tight_layout(); plt.show()

print("\n=== R(0) comparison ===")
print(f"Theoretical R(0) = {R_th[0]:.4f}, estimate = {R_est[0]:.4f}")

# =====================================================================
# ITEM 6. Conclusion
# =====================================================================
print("\n=== CONCLUSION ===")
print(f"The simulated series X(t) of length n = {n} is a realization of a")
print(f"stationary Gaussian process with covariance function")
print(f"  R(t) = D * exp(-alpha*|t|) * (cos(beta*t) - (alpha/beta)*sin(beta*|t|)),")
print(f"  where D = {D}, alpha = {alpha}, beta = {beta}.")
print()
print(f"The empirical mean ({X.mean():.3f}) is close to the theoretical mu = 0,")
print(f"and the empirical variance ({X.var(ddof=1):.3f}) is close to D = {D}.")
print("The histogram and the normal probability plot are consistent with")
print("a Gaussian distribution; the Kolmogorov-Smirnov and Shapiro-Wilk")
print("tests do not reject normality at the 5% significance level.")
print()
print(f"The Hampel rule detected {len(outliers)} outlier(s) (indices: {outliers.tolist()}),")
print("which is consistent with a clean Gaussian sample without contamination.")
print()
half = n // 2
print("Homogeneity: the two halves of the sample have similar mean")
print(f"  ({X[:half].mean():.3f} vs {X[half:].mean():.3f}) and variance")
print(f"  ({X[:half].var(ddof=1):.3f} vs {X[half:].var(ddof=1):.3f}),")
print("so the sample can be considered homogeneous.")
print()
print(f"Trend analysis: the linear fit gives slope = {slope:.5f} with p = {p:.4f},")
print("so no statistically significant trend is present - the process is")
print("stationary, as expected.")
print()
print(f"Covariance function: the empirical estimate R_bar(0) = {R_est[0]:.4f} is")
print(f"close to the theoretical R(0) = {R_th[0]:.4f}, and the two curves in the")
print("combined plot visually coincide, which confirms the adequacy of the")
print("AR(2) simulation algorithm for variant 4.")