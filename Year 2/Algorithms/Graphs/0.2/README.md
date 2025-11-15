### Problem 0.2 — Canonical Representation of a Rooted Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

A directed graph representing a **rooted tree** is given. Vertices are numbered from 1 to n. All edges are directed from the root toward the leaves. Output the **canonical representation** of this tree.

The canonical representation of a rooted tree with n vertices is an array `P` of length `n`, where `pi` is the parent of vertex `i`. If vertex `i` is the root, then `pi = 0`.

---

### Input

The first line contains an integer `n` `(1 ≤ n ≤ 100,000)` — the number of vertices.  
Each of the next `n−1` lines contains two integers `u` and `v` `(1 ≤ u, v ≤ n)` — an edge from `u` to `v`. It is guaranteed that the graph is a rooted tree.

---

### Output

Print `n` integers — the elements of the array `P`.  

---

### Example

<table>
  <tr>
    <th>Input</th>
    <th>Output</th>
  </tr>

  <tr>
    <td>
      <pre>
6
3 2
5 4
3 1
3 5
5 6
      </pre>
    </td>
    <td>
      <pre>
3 3 0 5 3 5
      </pre>
    </td>
  </tr>
</table>