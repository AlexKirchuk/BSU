### Problem 0.8 — String Transformation

**Input file:** `in.txt`  
**Output file:** `out.txt`  
**Time limit:** 1 s  
**Memory limit:** no

Given two non-empty strings `A` and `B` consisting of lowercase Latin letters, with lengths ≤ 1000, transform string `A` into string `B` with the **minimum total cost**.  

The costs are defined as:

- **Deletion** of a character from `A`: `x` points  
- **Insertion** of a character into `A`: `y` points  
- **Replacement** of a character in `A` with any other character: `z` points

---

### Input

- First three lines contain integers `x`, `y`, `z` — the costs of deletion, insertion, and replacement `(1 ≤ x, y, z ≤ 10^6)`.  
- Fourth line: string `A`  
- Fifth line: string `B`  

Both strings contain only lowercase letters.

---

### Output

- Print a single integer — the **minimum total cost** to transform `A` into `B`.

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
3
1
abcd
bce
</pre>
    </td>
    <td>
<pre>
3
</pre>
    </td>
  </tr>
</table>