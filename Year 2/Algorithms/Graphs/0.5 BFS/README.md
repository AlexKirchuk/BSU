### Problem 0.5 — Breadth-First Search (BFS) Labeling

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

A **directed graph** is given by its adjacency matrix. Perform a **breadth-first search (BFS)**.  
When multiple vertices are candidates for the next visit, always choose the vertex with the smallest number.  
During BFS, when a vertex is visited for the first time, assign it a label (labels start from 1).  
Continue BFS until all vertices are labeled. Determine the label assigned to each vertex.

---

### Input

The first line contains an integer `n` `(1 ≤ n ≤ 100)` — the number of vertices.  
The next `n` lines each contain `n` integers — the adjacency matrix of the graph.  
All diagonal elements are guaranteed to be zero. Numbers are separated by spaces.

---

### Output

Print `n` integers — the label assigned to each vertex.

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
7
0 1 1 0 0 0 0
0 0 0 0 1 0 0
0 1 0 1 1 0 0
0 1 0 0 1 0 0
0 0 0 0 0 1 0
0 0 0 1 0 0 0
0 0 0 0 0 1 0
      </pre>
    </td>
    <td>
      <pre>
1 2 3 5 4 6 7
      </pre>
    </td>
  </tr>
</table>