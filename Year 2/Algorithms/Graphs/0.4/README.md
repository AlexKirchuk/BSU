### Problem 0.4 — Canonical Representation of a Rooted Tree (from Adjacency Matrix)

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

A directed graph representing a **rooted tree** is given. Vertices are numbered from 1 to n. All edges are directed from the root toward the leaves. Output the **canonical representation** of this tree.

The canonical representation of a rooted tree with n vertices is an array `P` of length `n`, where `pi` is the parent of vertex `i`. If vertex `i` is the root, then `pi = 0`.

---

### Input

The first line contains an integer `n` `(1 ≤ n ≤ 100)` — the number of vertices.  
Each of the next `n` lines contains `n` integers — the adjacency matrix of the graph.  
If there is an edge from vertex `i` to vertex `j`, then the j-th number in the i-th row is `1`; otherwise it is `0`.  
It is guaranteed that the graph is a rooted tree.

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
0 0 0 0 0 0
0 0 0 0 0 0
1 1 0 0 1 0
0 0 0 0 0 0
0 0 0 1 0 1
0 0 0 0 0 0
      </pre>
    </td>
    <td>
      <pre>
3 3 0 5 3 5
      </pre>
    </td>
  </tr>
</table>