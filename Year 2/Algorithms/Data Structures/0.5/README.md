### Problem 0.5 — Road Construction

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

Berland consists of `n` cities. Initially, all cities are isolated — there are no roads between any cities.

Roads will be added one by one.  
After each added road, you must determine **how many connected components** currently exist among the cities.

---

### Input

The first line contains two integers:

- `n` — number of cities  
- `q` — number of road-addition queries  
  \[
  1 \le n, q \le 500{,}000
  \]

Each of the next `q` lines contains two integers `u` and `v` — the cities between which a new road is built:

- `1 ≤ u, v ≤ n`
- `u ≠ v`
- No pair of cities receives more than one road.

---

### Output

For each query (i.e., after adding each road), output a single number —  
**the current number of connected components** in the graph.

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
5 5
1 2
3 4
1 3
3 5
1 5
</pre>
    </td>
    <td>
<pre>
4
3
2
1
1
</pre>
    </td>
  </tr>
</table>