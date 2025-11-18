# Recurrence Relations — Problem Set

This directory contains selected problems focused on **recurrence relations** and **dynamic programming**.  
The tasks cover combinatorial sequences, counting problems, matrix chain multiplication, string transformations, and subsequence analysis.

These problems develop strong intuition for identifying recurrence patterns and designing efficient algorithms.

---

## 📘 List of Problems

### **0.1 — Frog Path**  
A frog jumps on lily pads arranged in a row.  
It can jump forward by 2 or 3 pads at a time and eats mosquitoes on each pad it lands on.  
Determine the **maximum number of mosquitoes** the frog can eat and the sequence of pads visited.

### **0.2 — Binary Strings with K Ones (Simple Version)**  
Given integers `N` and `K`, count the number of binary strings of length `N` containing exactly `K` ones.  
Output the count modulo `10^9 + 7`.

### **0.3 — Binary Strings with K Ones (Hard Version)**  
Similar to 0.2 but with larger constraints (`N ≤ 10^6`).  
Compute the count modulo `10^9 + 7`.

### **0.4 — Matrix Chain Multiplication Order**  
Given dimensions of `s` matrices, determine the optimal order of multiplication to **minimize the number of scalar multiplications**.

### **0.5 — Longest Common Subsequence (LCS)**  
Given two sequences of length `n`, compute the **length of the LCS** and report the **indices of matching elements** in both sequences.

### **0.6 — Minimal Palindrome**  
Given a string, remove the **minimal number of characters** to form a palindrome.  
Output the **length** of the resulting palindrome and one possible palindrome.

### **0.7 — Longest Increasing Subsequence (LIS)**  
Given a sequence of integers, compute the **length of the longest strictly increasing subsequence** using an algorithm with `O(n log n)` complexity.

### **0.8 — String Transformation with Costs**  
Transform string `A` into string `B` using **insertions, deletions, and substitutions** with given costs.  
Compute the **minimal total penalty**.

---

## ⭐ Individual Problem (Advanced)

### **Problem 63 — Ali-Baba and Coins**  
Ali-Baba collects coins placed along a road, each with a **position and deadline**.  
Determine the **minimal time** needed to collect all coins or report if it is impossible.

---

## ⚡ Optional Tasks (Advanced+)

These additional tasks are more challenging or combinatorial in nature. They are optional but recommended for advanced practice.

### **Problem 20 — Longest Palindromic Subsequence**  
Given a string, find the **longest palindromic subsequence** that can be obtained by deleting characters (without reordering).  
If multiple palindromes of maximal length exist, output the **lexicographically smallest and largest**.

### **Problem 35.1 — Attractive Tile Patterns**  
Count the number of distinct patterns of black and white tiles of size `m × n` such that **no 2×2 square is monochromatic**.  
Patterns differing by **rotation, reflection, or shift** are considered distinct.

---

This subset focuses exclusively on recurrence-relation and dynamic-programming tasks to strengthen skills in **state definition, recurrence formulation, and optimization strategies**.