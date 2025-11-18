### Problem 0.10 — Hash Table with Linear Probing

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

A hash table consists of `m` cells numbered 0 to m-1.  
**Collision resolution** uses **open addressing** with linear probing:

h(x, i) = ((x mod m) + c * i) mod m

- x — the key  
- i — the attempt number (starting from 0)  
- c — a constant  

Keys are inserted **sequentially**.  
If a key is already present, it is **not inserted again**.

Your task is to determine which key ends up in each cell after all insertions.

---

### Input

- The first line contains three integers: m c n  

  - 2 ≤ m ≤ 10,000 — table size  
  - 1 ≤ c ≤ m-1 — linear probing step, coprime with m  
  - 0 ≤ n ≤ 10,000 — number of keys to insert

- The next n lines each contain an integer key (0 ≤ key ≤ 10^9).  
  - Keys may repeat  
  - Table has enough space for all **unique** keys

---

### Output

Print exactly m integers: the content of each cell from 0 to m-1.  
- If a cell is empty, print -1.  
- Otherwise, print the key stored in that cell.

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
10 1 9
11
21
35
4
32
5
6
70
100
</pre>
    </td>
    <td>
<pre>
70 11 21 32 4 35 5 6 100 -1
</pre>
    </td>
  </tr>
</table>