Problem 0.1. Construct the adjacency matrix
Input file name: input.txt
Output file name: output.txt
Time limit: 1 s
Memory limit: 64 MB

An undirected graph is given by its edge list. Construct the adjacency matrix of this graph. It is guaranteed that the graph contains no loops or multiple edges.

Input
The first line contains two integers n and m — the number of vertices (1 ≤ n ≤ 100) and the number of edges (0 ≤ m ≤ n(n − 1)/2). The vertices are numbered from 1 to n. Each of the following m lines describes an edge: each line contains two integers u and v (1 ≤ u, v ≤ n, and u ≠ v), which are connected by an edge.

Output
Print the adjacency matrix of the graph: n lines with n numbers each. Every number must be 0 or 1, and the numbers in each line must be separated by spaces.