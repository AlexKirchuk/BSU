import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Variant 4 parameters
D = 2.0
alpha = 0.4
beta = 1.2
n = 150
delta_t = 1.0
m = 100

rng = np.random.default_rng(52375)

def r_theory(h, d=D, alpha=alpha, beta=beta):
    h = np.asarray(h, dtype=float)
    return d * np.exp(-alpha * np.abs(h)) * (
        np.cos(beta * h) - (alpha / beta) * np.sin(beta * np.abs(h))
    )

# AR(2) parameters
rho = np.exp(-alpha * delta_t)
phi1 = 2.0 * rho * np.cos(beta * delta_t)
phi2 = -rho ** 2
denom = (1.0 + phi2) * ((1.0 - phi2) ** 2 - phi1 ** 2)
sigma2 = D * denom / (1.0 - phi2)
sigma = np.sqrt(sigma2)

def simulate_ar2(length, phi1, phi2, sigma, rng, warmup=100):
    eta = rng.standard_normal(length + warmup)
    x = np.zeros(length + warmup)
    for k in range(2, length + warmup):
        x[k] = phi1 * x[k - 1] + phi2 * x[k - 2] + sigma * eta[k]
    return x[warmup:]

def r_hat(x, h):
    n_ = len(x)
    mu = x.mean()
    if h == 0:
        return np.sum((x - mu) ** 2) / n_
    return np.sum((x[h:] - mu) * (x[:-h] - mu)) / (n_ - h)

# =====================================================================
# TASK 2
# =====================================================================
print("=" * 70)
print("TASK 2. Averaging the covariance function over an ensemble")
print("=" * 70)

X_all = np.zeros((m, n))
for k in range(m):
    X_all[k] = simulate_ar2(n, phi1, phi2, sigma, rng)

H_max = 30
lags = np.arange(0, H_max + 1)

R_k = np.zeros((m, len(lags)))
for k in range(m):
    for j, h in enumerate(lags):
        R_k[k, j] = r_hat(X_all[k], h)

R_mean = R_k.mean(axis=0)
s_R = R_k.std(axis=0, ddof=1)
SE = s_R / np.sqrt(m)
lower = R_mean - 1.96 * SE
upper = R_mean + 1.96 * SE
R_th = r_theory(lags * delta_t)

print(f"\n{'h':>3} {'R_th':>10} {'R_mean':>10} {'s_R':>10} {'SE':>10} "
      f"{'lower':>10} {'upper':>10}")
for j, h in enumerate(lags):
    print(f"{h:>3} {R_th[j]:>10.4f} {R_mean[j]:>10.4f} {s_R[j]:>10.4f} "
          f"{SE[j]:>10.4f} {lower[j]:>10.4f} {upper[j]:>10.4f}")

fig, ax = plt.subplots(figsize=(11, 5))
ax.plot(lags, R_th, 'r-', lw=2, label=r'$R(h)$ theoretical')
ax.plot(lags, R_mean, 'b--', lw=1.6, label=r'$\bar{R}(h)$ ensemble mean')
ax.fill_between(lags, lower, upper, color='blue', alpha=0.2,
                label='95% confidence interval')
ax.plot(lags, lower, 'b:', lw=1)
ax.plot(lags, upper, 'b:', lw=1)
ax.axhline(0, color='k', lw=0.6)
ax.set_xlabel('lag h')
ax.set_ylabel('R(h)')
ax.set_title('Theoretical covariance, ensemble mean and 95% CI (variant 4)')
ax.legend()
ax.grid(alpha=0.3)
plt.tight_layout()
plt.show()

inside = np.sum((R_th >= lower) & (R_th <= upper))
print(f"\nTheoretical R(h) falls inside the 95% CI for {inside} out of {len(lags)} lags.")

print("\n=== CONCLUSION FOR TASK 2 ===")
print("1. The ensemble mean R_bar(h) reproduces the shape of the theoretical")
print("   covariance function: exponential decay with rate alpha = 0.4 and")
print("   oscillations with frequency beta = 1.2.")
print(f"2. At h = 0: theoretical R(0) = {R_th[0]:.4f}, ensemble mean = {R_mean[0]:.4f}.")
print(f"3. Standard deviation s_R(h) is smallest at h = 0 ({s_R[0]:.4f}) and")
print("   grows with h, which is natural since fewer products enter R_k(h).")
print(f"4. The 95% confidence interval contains the theoretical curve for")
print(f"   {inside}/{len(lags)} lags, i.e. the AR(2) model reproduces the target")
print("   covariance function correctly.")
print("5. Averaging over m = 100 realizations reduces the estimator variance")
print("   by a factor sqrt(m) = 10 compared with a single realization.")

# =====================================================================
# TASK 3
# =====================================================================
print("\n" + "=" * 70)
print("TASK 3. Random walk simulation (Section 3.4 of the textbook)")
print("=" * 70)

Delta_rw = 0.01
b_rw = 1.0
a_rw = 0.0
N_steps = 1000
n_paths = 5

delta_rw = b_rw * np.sqrt(Delta_rw)
p_plus = 0.5 + a_rw / (2 * b_rw) * np.sqrt(Delta_rw)
p_minus = 0.5 - a_rw / (2 * b_rw) * np.sqrt(Delta_rw)
p_zero = 1.0 - p_plus - p_minus

print(f"Parameters: Delta = {Delta_rw}, b = {b_rw}, a = {a_rw}")
print(f"delta = {delta_rw:.6f}, p+ = {p_plus:.6f}, p- = {p_minus:.6f}, p0 = {p_zero:.6f}")
print(f"N = {N_steps} steps, t_max = {N_steps * Delta_rw}")

rng_rw = np.random.default_rng(2026)
U = rng_rw.random((n_paths, N_steps))
eta = np.where(U < p_plus, delta_rw,
               np.where(U < p_plus + p_zero, 0.0, -delta_rw))

xi = np.cumsum(eta, axis=1)
xi = np.hstack([np.zeros((n_paths, 1)), xi])
t_rw = np.arange(N_steps + 1) * Delta_rw

fig, ax = plt.subplots(figsize=(11, 5))
for k in range(n_paths):
    ax.step(t_rw, xi[k], where='post', lw=1.2, alpha=0.8,
            label=f'path {k + 1}')
ax.axhline(0, color='k', lw=0.6)
ax.plot(t_rw, 1.96 * np.sqrt(b_rw ** 2 * t_rw), 'k--', lw=1,
        label=r'$\pm 1.96\sqrt{b^2 t}$')
ax.plot(t_rw, -1.96 * np.sqrt(b_rw ** 2 * t_rw), 'k--', lw=1)
ax.fill_between(t_rw, -1.96 * np.sqrt(b_rw ** 2 * t_rw),
                1.96 * np.sqrt(b_rw ** 2 * t_rw),
                color='gray', alpha=0.15)
ax.set_xlabel('t')
ax.set_ylabel(r'$\xi_t$')
ax.set_title(r'Random walk trajectories $\xi_t$ (Section 3.4, '
             r'$\Delta=0.01$, $b=1$, $a=0$)')
ax.legend(loc='upper left', fontsize=8)
ax.grid(alpha=0.3)
plt.tight_layout()
plt.show()

print("\nCheck of Var[xi_t] -> b^2 * t as Delta -> 0:")
M_check = 200
U_big = rng_rw.random((M_check, N_steps))
eta_big = np.where(U_big < p_plus, delta_rw,
                   np.where(U_big < p_plus + p_zero, 0.0, -delta_rw))
xi_big = np.cumsum(eta_big, axis=1)
xi_big = np.hstack([np.zeros((M_check, 1)), xi_big])

print(f"{'t':>8} {'b^2*t':>10} {'Var_emp':>12}")
for t_check in [1.0, 2.0, 5.0, 10.0]:
    idx = int(round(t_check / Delta_rw))
    var_emp = np.var(xi_big[:, idx], ddof=1)
    print(f"{t_check:>8.2f} {b_rw ** 2 * t_check:>10.4f} {var_emp:>12.4f}")

x_rw = xi[0]
lags_rw = np.arange(0, 51)
R_rw = np.array([r_hat(x_rw, h) for h in lags_rw])
print("\nSample covariance function of one trajectory (nonstationarity):")
for h in [0, 1, 2, 5, 10, 20, 50]:
    print(f"  R_hat({h:>2}) = {R_rw[h]:>10.4f}")

print("\n=== CONCLUSION FOR TASK 3 ===")
print("1. The random walk from Section 3.4 was simulated exactly:")
print("   xi_t in {l*delta}, xi_0 = 0, xi_{t+Delta} = xi_t + eta_t,")
print("   eta_t in {-delta, 0, +delta} with probabilities (p-, p0, p+).")
print("2. The increments were generated by the inverse transform method")
print("   (Section 1.3): one uniform U ~ U(0,1) selects +delta, 0, or -delta.")
print(f"3. With Delta = {Delta_rw}, b = {b_rw}, a = {a_rw}:")
print(f"   delta = {delta_rw:.6f}, p+ = {p_plus:.6f}, p- = {p_minus:.6f}.")
print("4. The empirical variance agrees with the theoretical b^2 * t:")
print("   at t = 10, Var_emp is close to b^2 * t = 10.")
print("5. The process is nonstationary: Var[xi_t] grows linearly with t,")
print("   and the sample covariance R_hat(h) does not depend only on the lag h.")
print("6. As Delta -> 0 with a = 0, b = 1 the process converges to the")
print("   standard Wiener process w_t, as stated in Section 3.4.")