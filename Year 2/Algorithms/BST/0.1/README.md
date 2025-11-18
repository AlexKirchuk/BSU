### Problem 0.1 — Build a Binary Search Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

Given a sequence of keys, build a **Binary Search Tree (BST)** by inserting the keys in the order they appear in the input.

If a key is already present in the tree, it must be **ignored** (BST keys are unique by definition).

After constructing the tree, perform a **preorder left traversal**  
(visit: **root → left subtree → right subtree**)  
and output the visited keys.

---

### Input

The input file contains a sequence of integers — the keys of the vertices,  
one per line, in the order of insertion.

- Keys are unique; duplicate keys must be ignored.

---

### Output

Print the sequence of keys obtained by a **preorder left traversal** of the final BST.  
Each key must be printed on its own line.

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
5
2
1
4
8
7
</pre>
    </td>
  </tr>
</table>