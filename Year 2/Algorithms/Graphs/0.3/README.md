### Problem 0.3 — Construct the Adjacency List

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 128 MB

An **undirected graph** is given by its edge list. Construct the adjacency list of this graph. It is guaranteed that the graph contains no loops or multiple edges.

---

### Input

The first line contains two integers `n` and `m` — the number of vertices  
`(1 ≤ n ≤ 100,000)` and the number of edges `(0 ≤ m ≤ 200,000)`.  

Vertices are numbered from 1 to `n`.  
Each of the next `m` lines contains two integers `u` and `v` `(1 ≤ u, v ≤ n, u ≠ v)` — vertices connected by an edge.

---

### Output

Print `n` lines — the adjacency list of the graph.  
On the i-th line, first print the number of vertices adjacent to vertex i, followed by their numbers in any order, separated by spaces.

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
5 4
1 2
4 3
2 4
2 3
      </pre>
    </td>
    <td>
      <pre>
1 2
3 3 4 1
2 2 4
2 2 3
0
      </pre>
    </td>
  </tr>
</table>