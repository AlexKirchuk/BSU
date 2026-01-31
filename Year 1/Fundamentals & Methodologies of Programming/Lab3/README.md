# Lab 3 — Computation of a Series

## Description

Compute the value of the series:

S = Σ (x^(2n+1) * sin(n*x)) / (2n + 1),  n = 5 .. m

for a given value of **m**, where **x** varies from **a** to **b** with a step **h**.

The results must be presented in the form of a table.

---

## Algorithm Idea

1. First, compute the value of the series for a given **x**.
2. The series value is accumulated using a loop from **n = 5** to **n = m**.
3. Each next term of the series is obtained from the previous one by multiplying by the corresponding factor.
4. There is no need to reset the series term at each iteration — it is sufficient to update it multiplicatively.

---

## Output Format

The program outputs a table with the following columns:

* **x** — the current argument value
* **Using Sin(x)** — value computed using a custom implementation of the sine function
* **Using sin(x)** — value computed using the standard library `sin()` function

---

## Test Cases

### Test 1

**Input:**

```
a = 1, b = 5, h = 1, m = 10
```

**Output:**

```
------------------------------------------------------
|  x  |   Using  Sin(x)   |   Using sin(x)   |
------------------------------------------------------
|    1|             -0.0108857|            -0.0108871|
|    2|                  69953|               69952.7|
|    3|            -4.3981e+08|          -4.39808e+08|
|    4|            1.42271e+11|           1.42274e+11|
|    5|           -5.07005e+12|          -5.07095e+12|
------------------------------------------------------
```

---

### Test 2

**Input:**

```
a = -5, b = 5, h = 1, m = 15
```

**Output:**

```
------------------------------------------------------
|  x  |   Using  Sin(x)   |   Using sin(x)   |
------------------------------------------------------
|   -5|           -5.30532e+19|          -5.30553e+19|
|   -4|           -4.99071e+16|          -4.99047e+16|
|   -3|            1.50281e+13|           1.50274e+13|
|   -2|           -6.07874e+07|          -6.07874e+07|
|   -1|            -0.00513166|           -0.00513021|
|    0|                      0|                     0|
|    1|            -0.00512895|           -0.00513021|
|    2|           -6.07877e+07|          -6.07874e+07|
|    3|            1.50275e+13|           1.50274e+13|
|    4|           -4.99067e+16|          -4.99047e+16|
|    5|           -5.30505e+19|          -5.30553e+19|
------------------------------------------------------
```

---

### Test 3

**Input:**

```
a = 0, b = 4, h = 2, m = 6
```

**Output:**

```
------------------------------------------------------
|  x  |   Using  Sin(x)   |   Using sin(x)   |
------------------------------------------------------
|    0|                      0|                     0|
|    2|               -439.406|               -439.41|
|    4|           -4.32676e+06|          -4.32669e+06|
------------------------------------------------------
```

---

### Test 4

**Input:**

```
a = -60, b = 40, h = 20, m = 20
```

**Output:**

```
------------------------------------------------------
|  x  |   Using  Sin(x)   |   Using sin(x)   |
------------------------------------------------------
|  -60|           -1.71984e+70|          -1.72471e+70|
|  -40|            1.05408e+64|           1.05418e+64|
|  -20|            -4.5622e+51|          -4.56198e+51|
|    0|                      0|                     0|
|   20|           -4.56219e+51|          -4.56198e+51|
|   40|            1.05409e+64|           1.05418e+64|
------------------------------------------------------
```

---

### Test 5

**Input:**

```
a = 1, b = 5, h = 1, m = 200
```

**Output:**

```
------------------------------------------------------
|  x  |   Using  Sin(x)   |   Using sin(x)   |
------------------------------------------------------
|    1|             -0.0385999|            -0.0386022|
|    2|          -8.30031e+117|         -8.29972e+117|
|    3|           2.76805e+187|          2.77304e+187|
|    4|           5.56876e+238|          5.56928e+238|
|    5|           4.14013e+277|           4.1396e+277|
------------------------------------------------------
```

---

## Note

There is no practical sense in choosing larger values of **b** and **m**, since numerical overflow occurs due to the floating-point limit (approximately ±1.7 × 10³⁰⁸).
