### Problem 0.0 — Sum of Keys in a Binary Search Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** no limit

A binary search tree (BST) is built by inserting integer keys one by one.  
Keys are 32-bit signed integers (range `-2^31` to `2^31 − 1`).  
If an insertion attempts to add a key that is already present in the tree, that key is ignored (BST contains unique keys).

Compute the sum of keys of all nodes in the resulting tree.

---

### Input

The input contains a sequence of integers — the keys to insert into the BST, given one per line. The sequence length is not given explicitly (read until end of file).

---

### Output

Output a single integer — the sum of all keys in the constructed tree.

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
5
2
4
1
8
7
      </pre>
    </td>
    <td>
      <pre>
27
      </pre>
    </td>
  </tr>
</table>