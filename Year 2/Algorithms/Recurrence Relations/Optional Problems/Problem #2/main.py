with open("in.txt", "r") as fin:
    m = int(fin.readline())
    n = int(fin.readline())

if m > n:
    m, n = n, m

S = 1 << m

ok = [[True] * S for _ in range(S)]

for a in range(S):
    for b in range(S):
        good = True
        for i in range(m - 1):
            a0 = (a >> i) & 1
            a1 = (a >> (i + 1)) & 1
            b0 = (b >> i) & 1
            b1 = (b >> (i + 1)) & 1
            if a0 == a1 == b0 == b1:
                good = False
                break
        ok[a][b] = good

dp = [1] * S

for _ in range(1, n):
    ndp = [0] * S
    for a in range(S):
        if dp[a] != 0:
            for b in range(S):
                if ok[a][b]:
                    ndp[b] += dp[a]
    dp = ndp

ans = sum(dp)

with open("out.txt", "w") as fout:
    fout.write(str(ans))