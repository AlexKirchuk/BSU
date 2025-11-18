### Problem 0.4 — Huffman Coding (Hard Version)

**Input file:** `huffman.in`  
**Output file:** `huffman.out`  
**Time limit:** 0.5 s  
**Memory limit:** 256 MB

Huffman coding (D. A. Huffman) is a prefix coding method that minimizes the total encoded length of a text by assigning different bit-length codes to different symbols.

You are given only the frequencies of each symbol, not the text itself — but this is enough, since the total encoded length depends solely on symbol frequencies.

---

### Huffman Tree Construction

Suppose the alphabet contains `n` symbols, and the `i`-th symbol occurs `p_i` times.

1. Initially, each symbol is considered an **active** node of the future Huffman tree, labeled with its frequency `p_i`.
2. Repeatedly perform the following step:
   - Take **two active nodes with the smallest labels**.
   - Create a new node whose label is the **sum** of their labels.
   - Make this new node the **parent** of the two selected nodes.
   - The two old nodes are removed from the active set; the new node becomes active.
3. Continue until exactly one active node remains — the root of the Huffman tree.

Each symbol corresponds to a **leaf**.  
The **length of the Huffman code** of a symbol equals the **distance from the root to its leaf**.

If each left/right edge is labeled `0` or `1`, the code of each symbol is the sequence of labels along the path from root to leaf.

---

### Goal

Compute the **total length of the encoded text in bits**, i.e.:

\[
\sum_{i=1}^{n} p_i \cdot \text{code\_length}(i)
\]

You must design an algorithm that runs in **O(n)** time, where `n` is the number of frequency values.

---

### Input

- The first line contains an integer `n`, the number of symbols  
  \(2 \le n \le 2{,}500{,}000\).
- The second line contains `n` integers `p_i` — the frequencies of the symbols  
  \(1 \le p_i \le 10^9\),  
  and the sequence is sorted non-decreasingly:  
  \(p_i \le p_{i+1}\).

---

### Output

Print a single integer — the total length (in bits) of the text after Huffman encoding.

---

### Example

<table>
  <tr>
    <th>huffman.in</th>
    <th>huffman.out</th>
  </tr>

  <tr>
    <td>
<pre>
6
1 1 2 2 5 8
</pre>
    </td>
    <td>
<pre>
42
</pre>
    </td>
  </tr>
</table>