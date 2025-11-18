### Problem 0.3 — Is the Binary Tree a Binary Search Tree?

**Input file:** `bst.in`  
**Output file:** `bst.out`  
**Time limit:** 1 s  
**Memory limit:** 64 MB

A binary tree is given. Check whether it is a binary search tree (BST) under the following convention:

- Equal keys are allowed in the tree.
- For the tree to be a BST, every node `x` must satisfy:
  - All keys in the **left** subtree are **strictly less** than the key of `x`.
  - All keys in the **right** subtree are **greater than or equal to** the key of `x`.

---

### Input

- The first line contains an integer `n` — number of nodes (1 ≤ n ≤ 8·10⁵).
- The second line contains the integer value stored in the **root** (`-2³¹` … `2³¹−1`).
- Each of the next `n − 1` lines contains:
  - `value` — node key (`-2³¹` … `2³¹−1`)
  - `p` — index of the line (0-based) where the parent node was specified (1 ≤ p ≤ n − 1)
  - `c` — either `L` (left child) or `R` (right child)

The description always forms a valid binary tree.

---

### Output

Print `YES` if the tree is a valid BST under the rules above, otherwise print `NO`.

---

### Example

<table>
  <tr>
    <th>bst.in</th>
    <th>bst.out</th>
  </tr>
  <tr>
    <td>
<pre>
7
1
2 1 L
4 2 L
3 1 R
5 2 R
6 4 L
7 4 R
</pre>
    </td>
    <td>
<pre>
NO
</pre>
    </td>
  </tr>
</table>