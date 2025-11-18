### Problem 0.5 — Longest Common Subsequence (LCS)

**Input file:** standard input  
**Output file:** standard output  
**Time limit:** 2 s  
**Memory limit:** 64 MB

You are given two sequences **A** and **B**, each of length `n`.

Your task is to find the largest integer `k` such that there exist two increasing sequences of indices:

- `0 ≤ i₁ < i₂ < … < iₖ < n`
- `0 ≤ j₁ < j₂ < … < jₖ < n`

A[i₁] = B[j₁],
A[i₂] = B[j₂],
…
A[iₖ] = B[jₖ].

In other words, find the **Longest Common Subsequence (LCS)** between sequences **A** and **B**, and also output the corresponding index sequences.

---

### Input

- The first line contains an integer `n` — the length of A and B  
  `1 ≤ n ≤ 1000`.
- The second line contains `n` integers `a[i]` — elements of sequence A  
  `1 ≤ a[i] ≤ 1000`.
- The third line contains `n` integers `b[j]` — elements of sequence B  
  `1 ≤ b[j] ≤ 1000`.

---

### Output

- On the first line, output `k` — the length of the LCS.  
- On the second line, output the indices `i₁ … iₖ`.  
- On the third line, output the indices `j₁ … jₖ`.  

If multiple valid LCS index sequences exist, output **any** of them.

---

### Example

<table>
  <tr>
    <th>standard input</th>
    <th>standard output</th>
  </tr>

  <tr>
    <td>
<pre>
6
1 2 3 3 4 6
1 6 3 3 2 4
</pre>
    </td>
    <td>
<pre>
4
0 2 3 4
0 2 3 5
</pre>
    </td>
  </tr>
</table>