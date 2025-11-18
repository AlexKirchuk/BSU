### Problem 0.8 — Range Sum Queries

**Input:** standard input  
**Output:** standard output  
**Time limit:** 2 s  
**Memory limit:** 256 MB

You are given an array `A` of length `n` (0-indexed):

\[
a_0, a_1, a_2, \dots, a_{n-1}
\]

There are **two types of queries**:

1. **Modification Query:**  
   Given an index `i` and a number `x`, **add** `x` to `a[i]`.
2. **Sum Query:**  
   Given indices `l` and `r`, compute the sum of elements on the half-open interval `[l, r)`, i.e.:  
   \[
   a_l + a_{l+1} + \dots + a_{r-1}
   \]

---

### Input

- The first line contains an integer `n` — the number of elements in the array  
  \(1 \le n \le 300{,}000\).
- The second line contains `n` integers `a_i` — the initial elements of the array  
  \(-10^9 \le a_i \le 10^9\).
- The third line contains an integer `q` — the number of queries  
  \(1 \le q \le 300{,}000\).
- The next `q` lines each describe a query:
  - **Modification Query:** `Add i x`  
    Add `x` to `a[i]` (`0 ≤ i < n`, `-10^9 ≤ x ≤ 10^9`)
  - **Sum Query:** `FindSum l r`  
    Compute the sum of elements from index `l` to `r-1` (`0 ≤ l < r ≤ n`)

---

### Output

For each **sum query**, output a single integer — the sum of elements on the specified interval.

---

### Example

<table>
  <tr>
    <th>standard input</th>
    <th>standard output</th>
  </tr>

  <tr>
    <td>
<pre>
5
10 30 40 -10 20
7
FindSum 1 2
FindSum 1 3
FindSum 1 4
FindSum 3 5
Add 4 -10
FindSum 3 5
FindSum 0 5
</pre>
    </td>
    <td>
<pre>
30
70
60
10
0
80
</pre>
    </td>
  </tr>
</table>