### Problem 35.2 — Attractive Tile Patterns (Hard Version)

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** no

The company **Broken Tiles** produces small black and white tiles.  
A wealthy client wants to assemble a rectangular figure using these tiles, with one important restriction:

> The figure must **not contain any 2×2 square fully composed of tiles of the same color**.

Any rectangle satisfying this condition is called **attractive**.

Since building such figures has become a fashionable hobby among the rich, the company director wants to know **how many different attractive n × m patterns** can be constructed.  
Only black and white tiles are allowed.  
Two patterns are considered different if at least one tile differs — **rotations or reflections do not matter**.

---

### Input

A single line containing two integers:

- `n` — number of rows  
  **(1 ≤ n ≤ 10¹⁰⁰)**
- `m` — number of columns  
  **(1 ≤ m ≤ 5)**

The value of `n` may be extremely large (up to 100 digits), while `m` is small.

---

### Output

Print a single integer — the number of attractive `n × m` patterns, **modulo 10000**.

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
3 3
      </pre>
    </td>
    <td>
      <pre>
322
      </pre>
    </td>
  </tr>
</table>

---

### Notes

- A **2×2 monochromatic square** is not allowed anywhere in the pattern.  
- Patterns that differ only by rotations, reflections, or shifts are still considered distinct.