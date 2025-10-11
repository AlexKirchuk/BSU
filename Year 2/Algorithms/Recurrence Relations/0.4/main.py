n = int(input())
dim = [0] * (n + 1)

for i in range(n):
	rows, cols = map(int, input().split())
	if i == 0: dim[i] = rows;
	dim[i + 1] = cols;

b = [[0] * (n + 1) for _ in range(n + 1)]

for l in range(2, n + 1):
    for i in range(1, n - l + 2):
        j = i + l - 1
        b[i][j] = float("inf")
        for k in range(i, j):
            cost = b[i][k] + b[k + 1][j] + dim[i - 1] * dim[k] * dim[j]
            b[i][j] = min(b[i][j], cost)

print(b[1][n])