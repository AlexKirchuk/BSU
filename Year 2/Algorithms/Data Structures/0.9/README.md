### Problem 0.9 — Segment Tree

**Input file:** `input.txt`  
**Output file:** `output.txt`  
**Time limit:** 1 s  
**Memory limit:** no limit

You are given a sequence of length `n` initialized with zeros:

s0, s1, ..., s(n-1)

There are several types of queries:

1. **Set**: set s[i] = v.
2. **Add**: add v to each element in the range [a, b].
3. **Sum**: find the sum of elements in the range [a, b].
4. **Min**: find the minimum element in the range [a, b].
5. **Max**: find the maximum element in the range [a, b].

Your task is to process all queries efficiently.

---

### Input

- The first line contains an integer `n` — the length of the sequence  
  1 ≤ n ≤ 300,000
- Each subsequent line describes a query:

| Query Type | Format |
|------------|--------|
| Set        | `1 i v` |
| Add        | `2 a b v` |
| Sum        | `3 a b` |
| Min        | `4 a b` |
| Max        | `5 a b` |

- The input ends with a line containing a single `0`.
- Constraints:
  - |v| ≤ 1,000,000
  - 0 ≤ i < n
  - 0 ≤ a ≤ b < n
- Total number of lines does not exceed 300,003.

---

### Output

For each query of type 3–5, output the result on a separate line.

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
2 0 4 7
3 2 3
1 2 -10
4 0 3
2 3 4 9
5 0 4
0
</pre>
    </td>
    <td>
<pre>
14
-10
16
</pre>
    </td>
  </tr>
</table>