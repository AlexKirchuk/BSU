### Problem 0.7 — Longest Increasing Subsequence (LIS)

**Input file:** input.txt  
**Output file:** output.txt  
**Time limit:** 1–5 s  
**Memory limit:** no

Given a sequence of integers `A` of length `n`, remove the **minimum number of elements** so that the remaining elements form a **strictly increasing subsequence**.  

The implemented algorithm should have **O(n log n)** complexity.

> **Note:** Strictly increasing means each next element of the subsequence is strictly greater than the previous one.

---

### Input

- The first line contains an integer `n` — the length of the sequence `(1 ≤ n ≤ 700000)`.  
- The second line contains `n` integers `A[i]` — the elements of the sequence `(-10^9 ≤ A[i] ≤ 10^9)`.

---

### Output

- Output a single integer — the **length of the longest strictly increasing subsequence**.

---

### Example

<table>
  <tr>
    <th>input.txt</th>
    <th>output.txt</th>
  </tr>

  <tr>
    <td>
<pre>
6
1 2 3 4 7 6
</pre>
    </td>
    <td>
<pre>
5
</pre>
    </td>
  </tr>
</table>