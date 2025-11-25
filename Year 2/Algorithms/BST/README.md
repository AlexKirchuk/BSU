# Binary Search Trees — Problem Set

This directory contains selected problems focused on **binary trees** and **binary search trees (BSTs)**.  
They cover tree construction, deletion, validation of BST properties, and analysis of tree paths.

These tasks develop strong intuition for working with hierarchical data structures.

---

## 📘 List of Problems

### **0.1 — Construct a Binary Search Tree**  
Build a BST from the given sequence of keys (ignoring duplicates) and output its **preorder left traversal**.

### **0.2 — Delete from a Binary Search Tree**  
From the input keys, construct a BST, delete the specified key using **right-deletion** (if it exists), and output the **preorder left traversal** of the resulting tree.

### **0.3 — Is the Binary Tree a Binary Search Tree?**  
A binary tree is given in a structured format.  
Determine whether it satisfies the BST property, assuming the definition where:

- Left subtree keys must be **strictly less** than the node’s key.  
- Right subtree keys must be **greater than or equal** to the node’s key.  
- Duplicate keys are allowed **only on the right**.

Output **YES** or **NO**.

---

## ⭐ Individual Problem (Advanced)

### **Problem 16 — Half-Paths in a BST After Root Deletion**  
You are given a BST.  
Delete its **root** using right-deletion.  
For every remaining node, compute how many **longest half-paths** pass through it.  
Output results using **preorder left traversal**.

---

This set focuses exclusively on binary-tree–related tasks to help solidify your understanding of BST mechanics and tree-based computations.