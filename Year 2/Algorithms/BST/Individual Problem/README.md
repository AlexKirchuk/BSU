### Problem 16 — Half-Paths in a BST After Root Deletion

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 1024 MB

You are given a sequence of keys inserted into a **Binary Search Tree (BST)** in the exact order they appear in the input.

After building the tree, you must **delete the root** using **right deletion**:

- If the root has two children, replace it with the **minimum node of its right subtree**, and then remove that node from the right subtree.

After deleting the root, the task is to compute, **for each remaining vertex**, how many **maximum-length half-paths** pass through it.

A **half-path** is a longest downward path starting at a vertex and going strictly into one of its subtrees.

If after deleting the root the tree contains only one vertex, we consider that there is **exactly one** maximum half-path of length 0.

---

### Input

The input file contains a sequence of integers — the keys of the vertices in the order they are inserted into the BST.  
It is guaranteed that the tree initially contains **at least two vertices**.

---

### Output

Perform a **preorder left traversal** of the resulting tree (root → left → right).

For each vertex, output on a separate line:

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
1
5
3
7
2
4
6
8
</pre>
    </td>
    <td>
<pre>
5 4
3 4
2 2
4 2
7 4
6 2
8 2
</pre>
    </td>
  </tr>
</table>