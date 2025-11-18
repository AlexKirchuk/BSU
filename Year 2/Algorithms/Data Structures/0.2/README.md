### Problem 0.2 — Binary Heap?

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

A complete binary tree with `n` nodes can be stored compactly in a one-dimensional array indexed from **1**.  
For a node at index `i`:

- its left child is at index `2i` (if it exists),
- its right child is at index `2i + 1` (if it exists).

A **binary heap** (specifically, a **Min-Heap**) is a complete binary tree in which every node has a key **less than or equal to** the keys of its children.

You are given an array of `n` integers.  
Determine whether this array can represent a valid **binary min-heap** under the above indexing rules.

Use of built-in heap verification functions (e.g., `std::is_heap`) is forbidden.

---

### Input

- The first line contains an integer `n` — the number of elements  
  `(1 ≤ n ≤ 100000)`.
- The second line contains `n` integers — the array elements, each with absolute value ≤ `10^9`.

---

### Output

Print:

- `Yes` — if the array represents a valid binary min-heap;
- `No` — otherwise.

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
10
9 17 16 25 21 20 60 25 40 33
</pre>
    </td>
    <td>
<pre>
Yes
</pre>
    </td>
  </tr>
</table>