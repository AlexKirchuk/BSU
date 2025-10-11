with open("input.txt", "r") as file:
    s = file.readline()
f = [[0] * (len(s)) for _ in range(len(s))]
for i in range(len(s)):
    f[i][i] = 1

for d in range(1, len(s)):
    for i in range(len(s) - d):
        j = i + d;
        if s[i] == s[j]:
            f[i][j] = f[i + 1][j - 1] + 2
        else:
            f[i][j] = max(f[i + 1][j], f[i][j - 1])
       
left = []
right = []
i = 0
j = len(s) - 1
while f[i][j] != 0:
    if  s[i] == s[j]:
        left.append(s[i])
        i += 1
        j -= 1
    elif f[i][j] == f[i + 1][j]:
        i += 1
    elif f[i][j] == f[i][j - 1]:
        j -= 1

for i in range(f[0][len(s) - 1] // 2 - 1, -1, -1):
    right.append(left[i])
pal = ''.join(left + right)

with open("output.txt", "w") as file:
    file.write(str(f[0][len(s) - 1]) + "\n")
    file.write(str(pal))