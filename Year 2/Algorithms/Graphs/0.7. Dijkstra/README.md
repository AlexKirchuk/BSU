### Problem 0.7 — Dijkstra's Algorithm

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 64 MB

An **undirected weighted pseudograph** is given, with vertices numbered from 1 to n.  
Find the length of the shortest path between vertex 1 and vertex n.  
It is guaranteed that a path from 1 to n exists.

---

### Input

The first line contains two integers `n` and `m` — the number of vertices `(1 ≤ n ≤ 200,000)` and the number of edges `(0 ≤ m ≤ 300,000)`.

Each of the next `m` lines contains three integers `ui, vi, wi` — the endpoints of the edge and its weight `(1 ≤ ui, vi ≤ n, 0 ≤ wi ≤ 11,111)`.

---

### Output

Print a single integer — the length of the shortest path from vertex 1 to vertex n.

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
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
      </pre>
    </td>
    <td>
      <pre>
5
      </pre>
    </td>
  </tr>
</table>