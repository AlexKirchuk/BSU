### Problem 0.1 — Binary Search

**Input:** standard input  
**Output:** standard output  
**Time limit:** 3 s  
**Memory limit:** 256 MB

Implement binary search on an array of integers sorted in **non-decreasing** order.  
Using built-in binary search functions from standard libraries is **not allowed**.

---

### Input

- The first line contains an integer `n` — the number of elements in the array  
  `(0 ≤ n ≤ 3 · 10^5)`.
- The second line contains `n` integers — the array elements.  
  Each integer is in the range `[−2^31, 2^31 − 1]`.  
  The array is sorted in non-decreasing order.
- The third line contains an integer `k` — the number of queries  
  `(0 ≤ k ≤ 3 · 10^5)`.
- The fourth line contains `k` integers — the query values.  
  Each query integer is in the range `[−2^31, 2^31 − 1]`.

---

### Output

For each query value `x`, output three integers `b l r`:

- `b = 1` if `x` is present in the array, otherwise `0`;
- `l` is the index of the **first element ≥ x**;
- `r` is the index of the **first element > x**.

Array elements are indexed from `0` to `n − 1`.

If no such element exists, the returned index must be `n`.

Each query result should be printed on a separate line.

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
4
1 2 2 3
5
0 1 2 3 4
</pre>
    </td>
    <td>
<pre>
0 0 0
1 0 1
1 1 3
1 3 4
0 4 4
</pre>
    </td>
  </tr>
</table>