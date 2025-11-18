### Problem 0.3 — Binomial Heap

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 64 MB

A **binomial tree** of degree \(k\), denoted \(B_k\), is defined recursively:

- \(B_0\) is a single vertex.
- For \(k \ge 1\), \(B_k\) is formed by linking two copies of \(B_{k-1}\): make the root of one copy a child of the root of the other.  

Equivalently, the root of \(B_k\) has children that are the roots of binomial trees \(B_{0}, B_{1}, \dots, B_{k-1}\).  
The number of nodes in \(B_k\) is \(2^{k}\).

A **binomial heap** is a collection of binomial trees of pairwise distinct degrees. That is, for each \(k \ge 0\), either \(B_k\) appears in the heap exactly once or it does not appear at all.

You are given the total number of nodes \(n\) in a binomial heap. Determine which binomial trees may compose this heap.

---

### Input

The input contains a single integer `n` — the total number of vertices in the heap.  
\(1 \le n \le 10^{18}\).

---

### Output

If it is possible to form a binomial heap with exactly `n` nodes, output the degrees \(k\) of the binomial trees that appear in the heap, one integer per line, in **increasing** order.

If there are multiple solutions, output any one of them. If there is no solution, output `-1`.

*(Note: each degree must appear at most once, and the sum of \(2^{k}\) over chosen degrees must equal `n`.)*

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
13
</pre>
    </td>
    <td>
<pre>
0
2
3
</pre>
    </td>
  </tr>
</table>