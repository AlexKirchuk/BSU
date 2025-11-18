### Problem 20 — Longest Palindromic Subsequence (Lexicographical Extremes)

**Input file:** standard input  
**Output file:** standard output  
**Time limit:** 2 s  
**Memory limit:** 256 MB

Given a string consisting of lowercase English letters (without spaces), a **palindrome** is a string that reads the same forwards and backwards.  

You need to find the **longest palindrome** that can be obtained from the input string by **deleting characters** (the order of characters cannot be changed).  
If there are multiple longest palindromes, output both the **lexicographically minimal** and **maximal** ones.

---

### Input

- A single line containing a string of lowercase letters, length `1` to `10,000`.

---

### Output

- First line: the **lexicographically minimal** longest palindrome.  
- Second line: the **lexicographically maximal** longest palindrome.  
- If the minimal and maximal palindromes are identical, print the same string on both lines.

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
abcbbaa
</pre>
    </td>
    <td>
<pre>
abbba
abcba
</pre>
    </td>
  </tr>
</table>

---

### Note

Strings `S` and `T` are in **lexicographical order** (dictionary order) if for the first position `i` where `S[i] != T[i]`, the character `S[i]` comes before `T[i]`.  

For example, `"acf"` is lexicographically less than `"ada"` because at the second character `'c' < 'd'`.