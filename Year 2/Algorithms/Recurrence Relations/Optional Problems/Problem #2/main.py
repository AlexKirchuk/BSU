with open("in.txt", "r") as fin:
    m = int(fin.readline())
    n = int(fin.readline())

if m > n:
    m, n = n, m

S = 1 << m

nexts = [[] for _ in range(S)]

for a in range(S):
    for b in range(S):
        good = True
        aa = a
        bb = b
        for i in range(m - 1):
            a0 = (aa >> i) & 1
            a1 = (aa >> (i + 1)) & 1
            b0 = (bb >> i) & 1
            b1 = (bb >> (i + 1)) & 1
            if a0 == a1 == b0 == b1:
                good = False
                break
        if good:
            nexts[a].append(b)

dp = [1] * S

for _ in range(1, n):
    ndp = [0] * S
    for a in range(S):
        da = dp[a]
        if da:
            for b in nexts[a]:
                ndp[b] += da
    dp = ndp

ans = sum(dp)

with open("out.txt", "w") as fout:
    fout.write(str(ans))