### Problem 0.7 — Road Destruction (Hard Version)

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1.25 s  
**Memory limit:** 256 MB

In Berland, there are n cities connected by m roads.  
Initially, the graph is **connected** (there is a path between any two cities).

There are q earthquakes, each destroying **exactly one road**.  
After each earthquake, determine whether the resulting graph remains **connected**.  
Destroyed roads are **permanently removed**.

---

### Input

- The first line contains three integers: n, m, q  
  1 ≤ n, m, q ≤ 750,000
- The next m lines each contain two integers u and v — the cities connected by that road  
  1 ≤ u, v ≤ n, u ≠ v  
  There is at most one road between any pair of cities.
- The next q lines each contain a single integer x_i — the index (1-based) of the road destroyed in the i-th earthquake.  
  Each road is destroyed at most once.

---

### Output

Print a string of length q consisting of zeros and ones.  
The i-th character is:

- 1 — if the graph is still connected after the i-th earthquake
- 0 — otherwise

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
4 6 6
1 2
2 3
3 4
4 1
3 1
4 2
1
6
2
5
4
3
</pre>
    </td>
    <td>
<pre>
110000
</pre>
    </td>
  </tr>
</table>