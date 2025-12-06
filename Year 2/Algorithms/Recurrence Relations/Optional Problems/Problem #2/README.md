### Problem 35.1 — Attractive Tile Patterns

**Input file:** `in.txt`  
**Output file:** `out.txt`  
**Time limit:** 1 s  
**Memory limit:** no

A company plans to lay patterns of black and white tiles in the yards of wealthy clients.  
Each tile is `1 × 1` meter. Yards are rectangular, of size `m × n` meters.  

A pattern is considered **attractive** if it does **not contain any 2×2 square fully covered with tiles of the same color**.  

The company wants to know **how many distinct attractive patterns** of size `m × n` can be made.  
Two patterns are considered different even if one is obtained from another by **rotation, reflection, or shift**.

---

### Input

- First line: integer `m` — the number of rows (`1 ≤ m ≤ 10`)  
- Second line: integer `n` — the number of columns (`1 ≤ n ≤ 30`)

---

### Output

- A single integer — the number of distinct attractive patterns.  
  Note: The answer may not fit in standard integer types.

---

### Example

<table>
  <tr>
    <th>in.txt</th>
    <th>out.txt</th>
  </tr>
  <tr>
    <td>
<pre>
2
2
</pre>
    </td>
    <td>
<pre>
14
</pre>
    </td>
  </tr>
</table>

---

### Note

- A **2×2 monochromatic square** is not allowed anywhere in the pattern.  
- Patterns that differ only by rotations, reflections, or shifts are still considered distinct.