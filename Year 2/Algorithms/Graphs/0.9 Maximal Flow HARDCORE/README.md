### Problem 0.9 — Maximum Flow (Hard Version)

**Input:** standard input  
**Output:** standard output  
**Time limit:** from 1 s to 10 s  
**Memory limit:** 256 MB

A directed graph \( G \) is given, containing \( n \) vertices and \( m \) directed edges.  
Each edge \((u, v)\) has a capacity \( c_{uv} \).

You must find a **maximum flow** from the **source** (vertex 1) to the **sink** (vertex n).

---

### Input

The first line contains two integers `n` and `m` — the number of vertices and edges in the graph  
`(1 ≤ n ≤ 200,000, 0 ≤ m ≤ 200,000)`.

Each of the next `m` lines contains three integers `ui, vi, wi` —  
a directed edge from vertex `ui` to vertex `vi` with capacity `wi`.

Constraints:

- `ui ≠ vi`  
- `1 ≤ ui, vi ≤ n`  
- `1 ≤ wi ≤ 1,000,000`

---

### Output

Print a single integer — the **maximum possible flow** from vertex `1` to vertex `n`.

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
5 5
1 2 10
2 3 10
3 4 9
4 5 12
5 1 100
      </pre>
    </td>
    <td>
      <pre>
9
      </pre>
    </td>
  </tr>
</table>

---

### Note

The goal of this problem is to test various maximum flow algorithms.  
One of the test cases has a 10-second time limit — this is a special stress test designed for algorithm evaluation.