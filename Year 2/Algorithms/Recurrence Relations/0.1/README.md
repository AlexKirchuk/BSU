### Problem 0.1 — Frog Path

**Input file:** standard input  
**Output file:** standard output  
**Time limit:** 1 s  
**Memory limit:** 256 MB

A frog is jumping on lily pads arranged in a single row, numbered from **1** to **n**.  

The frog starts on pad **1** and wants to reach pad **n**.  
However, it can only jump **forward** by **2** or **3** pads at a time.  
For example, from pad 1 it can jump to pad 3 or pad 4.

Each pad contains some mosquitoes. When the frog lands on pad *i*, it eats all `a[i]` mosquitoes on it.  

Your task is to plan the frog's route so that it eats the **maximum number of mosquitoes**.

---

### Input

- The first line contains an integer `n` — the number of lily pads  
  `1 ≤ n ≤ 100000`.
- The second line contains `n` nonnegative integers `a[i]` — the number of mosquitoes on each pad (`1 ≤ i ≤ n`)  
  `0 ≤ a[i] ≤ 1000`.

---

### Output

If the frog can reach the last pad:

1. On the first line, print the **maximum number of mosquitoes** the frog can eat.
2. On the second line, print the **sequence of pads** visited by the frog in increasing order.

If it is impossible to reach the last pad, print -1

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
6
1 100 3 4 1000 0
</pre>
    </td>
    <td>
<pre>
5
1 4 6
</pre>
    </td>
  </tr>
</table>