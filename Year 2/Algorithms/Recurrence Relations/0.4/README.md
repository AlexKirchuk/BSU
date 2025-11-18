### Problem 0.4 — Matrix Chain Multiplication Order

**Input file:** input.txt  
**Output file:** output.txt  
**Time limit:** 1 s  
**Memory limit:** 256 MB

You are given a sequence of `s` matrices  
**A₁, A₂, …, Aₛ**.

Your goal is to determine the order in which they should be multiplied so that the **number of atomic multiplication operations** is minimized.

All matrices are compatible for multiplication:  
the number of columns of matrix **Aᵢ** equals the number of rows of matrix **Aᵢ₊₁**.

Multiplying a `k × m` matrix by an `m × n` matrix produces a `k × n` matrix and requires exactly **k · m · n** atomic operations.

Matrix multiplication is associative, so the result is the same regardless of parenthesization — only the number of operations changes.

---

### Input

- The first line contains an integer `s` — the number of matrices  
  `2 ≤ s ≤ 100`.
- The next `s` lines each contain two integers `nᵢ` and `mᵢ` —  
  the dimensions of matrix **Aᵢ**, where  
  `1 ≤ nᵢ, mᵢ ≤ 100`.

It is guaranteed that `mᵢ = nᵢ₊₁` for all `1 ≤ i < s`.

---

### Output

Print one integer — the **minimum number of atomic multiplications** required to compute the product of all `s` matrices.

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
3
2 3
3 5
5 10
</pre>
    </td>
    <td>
<pre>
130
</pre>
    </td>
  </tr>
</table>

---

### Note

For the example above, two possible parenthesizations exist:

- **A₁(A₂A₃)**  
  Cost: `3 × 5 × 10 + 2 × 3 × 10 = 150 + 60 = 210`

- **(A₁A₂)A₃**  
  Cost: `2 × 3 × 5 + 2 × 5 × 10 = 30 + 100 = 130`

The second option is more efficient.