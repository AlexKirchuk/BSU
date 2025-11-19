# Graph Algorithms — Problem Set

This directory contains a collection of algorithmic problems focused on fundamental concepts in **graph theory**.  
The tasks cover basic graph representations as well as classical algorithms for traversal, shortest paths, and maximum flow.

The goal of this set is to build strong practical understanding of essential graph algorithms and data structures.

---

## 📘 List of Problems

### **0.1 — Construct the Adjacency Matrix**  
Build an adjacency matrix from an edge list.

### **0.2 — Canonical Form of a Rooted Tree (Edge List)**  
Determine the parent array of a rooted tree given as directed edges.

### **0.3 — Construct the Adjacency List**  
Build adjacency lists for an undirected graph.

### **0.4 — Canonical Form of a Rooted Tree (Adjacency Matrix)**  
Determine the parent of each vertex using an adjacency matrix.

### **0.5 — BFS Labeling**  
Assign labels to vertices in the order they are visited by BFS.

### **0.6 — DFS Labeling**  
Assign labels to vertices in the order they are discovered by DFS.

### **0.7 — Dijkstra’s Algorithm**  
Find the shortest path in a weighted undirected graph.

### **0.8 — Maximum Flow (Simple Version)**  
Compute maximum flow in a small directed network (up to 200 vertices).

### **0.9 — Maximum Flow (Hard Version)**  
Compute maximum flow in a large directed network (up to 200k vertices).  
Includes stress tests with up to 10-second time limits.

---

## ⭐ Individual Problem (Advanced)

### **Problem 19 — The Great Pyramid of Khufu**  
Inside a system of **N rooms** inside the Pyramid of Khufu, **M bidirectional teleportation devices** connect pairs of rooms.  
Each device consists of two independent modules located in different rooms, each activating periodically at integer time intervals.  
A device can be used **only when both modules activate simultaneously**.

Indiana Jones must reach **room N** from **room 1** as fast as possible, with movement between rooms taking **0.5 time units** once the device is available.

You must compute:

- the **minimum possible travel time**, and  
- the **sequence of device indices** used to reach room **N**.

A valid path is guaranteed to exist.

---

This set focuses on mastering graph representations, graph traversal, shortest-path algorithms, and modeling dynamic systems through graph-based structures.