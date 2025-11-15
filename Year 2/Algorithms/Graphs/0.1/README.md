### Problem 0.1 — Construct the Adjacency Matrix

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 64 MB

An undirected graph is given by its edge list. Construct the adjacency matrix of this graph.  
It is guaranteed that the graph contains no loops or multiple edges.

---

### Input

The first line contains two integers `n` and `m` — the number of vertices  
`(1 ≤ n ≤ 100)` and the number of edges  
`(0 ≤ m ≤ n(n − 1) / 2)`.

Vertices are numbered from 1 to `n`.

Each of the next `m` lines contains an edge: two integers `u` and `v`  
`(1 ≤ u, v ≤ n`, `u ≠ v)` — vertices connected by an edge.

---

### Output

Print the adjacency matrix of the graph:  
`n` lines with `n` numbers each (0 or 1).  
Numbers in each line must be separated by spaces.

---

## Examples

<table>
  <tr>
    <th>Input</th>
    <th>Output</th>
  </tr>

  <tr>
    <td><code>
3 2<br>
1 2<br>
2 3
    </code></td>
    <td><code>
0 1 0<br>
1 0 1<br>
0 1 0
    </code></td>
  </tr>

  <tr>
    <td><code>
4 3<br>
1 2<br>
1 3<br>
2 4
    </code></td>
    <td><code>
0 1 1 0<br>
1 0 0 1<br>
1 0 0 0<br>
0 1 0 0
    </code></td>
  </tr>
</table>