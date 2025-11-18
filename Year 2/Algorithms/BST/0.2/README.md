### Problem 0.2 — Delete a Key from a Binary Search Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** 256 MB

You are given a sequence of keys.  
First, build a **Binary Search Tree (BST)** by inserting the keys in the order they appear.  
All keys in a BST are **unique** — if a key that already exists is inserted again, it is ignored.

Then delete a specified key from the tree using **right deletion**  
(i.e., when deleting a node with two children, replace it with the minimum key in its **right** subtree).

After this, perform a **preorder left traversal**  
(**root → left subtree → right subtree**)  
and output the resulting sequence of keys.

---

### Input

- The first line contains an integer — the key to be deleted.
- The second line is empty.
- The remaining lines contain integers — the keys to be inserted into the BST,  
  one per line, in insertion order.
- The BST contains at least two vertices before deletion.

Duplicate keys must be ignored.

---

### Output

Print the keys of the resulting tree in **preorder left traversal**,  
one key per line.

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
2
 
4
2
1
3
5
</pre>
    </td>
    <td>
<pre>
4
3
1
5
</pre>
    </td>
  </tr>
</table>