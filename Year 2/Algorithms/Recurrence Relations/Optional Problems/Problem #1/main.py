from array import array

def build_next_prev(s):
    n = len(s)
    ALPH = 26
    next_pos = [[-1]*ALPH for _ in range(n+1)]
    for c in range(ALPH):
        next_pos[n][c] = -1
    for i in range(n-1, -1, -1):
        row_next = next_pos[i]
        row_next1 = next_pos[i+1]
        for c in range(ALPH):
            row_next[c] = row_next1[c]
        row_next[ord(s[i]) - 97] = i

    prev_pos = [[-1]*ALPH for _ in range(n)]
    first_row = prev_pos[0]
    for c in range(ALPH):
        first_row[c] = -1
    first_row[ord(s[0]) - 97] = 0
    for i in range(1, n):
        row_prev = prev_pos[i]
        row_prev1 = prev_pos[i-1]
        for c in range(ALPH):
            row_prev[c] = row_prev1[c]
        row_prev[ord(s[i]) - 97] = i

    return next_pos, prev_pos

def compute_dp_triangular(s):
    n = len(s)
    if n == 0:
        return []
    dp = [None] * n
    s_int = [ord(ch) for ch in s]

    for i in range(n-1, -1, -1):
        length = n - i
        row = array('h', [0]) * length
        row[0] = 1
        dp[i] = row
        if i == n-1:
            continue
        row_i1 = dp[i+1]
        for k in range(1, length):
            j = i + k
            if s_int[i] == s_int[j]:
                if j == i+1:
                    val = 2
                else:
                    val = 2 + row_i1[k-2]
            else:
                a = row_i1[k-1]
                b = row[k-1]
                val = a if a >= b else b
            row[k] = val
    return dp

def reconstruct(s, dp, next_pos, prev_pos, want_max=False):
    n = len(s)
    if n == 0:
        return ""
    total = dp[0][n-1]
    if total == 0:
        return ""
    left_part = []
    right_part = []
    l = 0
    r = n - 1
    need = total
    ALPH = 26

    while need > 1 and l <= r:
        chosen = -1
        if not want_max:
            cand_range = range(ALPH)
        else:
            cand_range = range(ALPH-1, -1, -1)
        for c in cand_range:
            i = next_pos[l][c]
            if i == -1 or i > r:
                continue
            j = prev_pos[r][c]
            if j == -1 or j < i:
                continue
            if i == j:
                continue
            if i+1 > j-1:
                inner = 0
            else:
                inner = dp[i+1][(j-1)-(i+1)]
            if 2 + inner == need:
                chosen = c
                chosen_i = i
                chosen_j = j
                break
        if chosen == -1:
            break
        ch = chr(chosen + 97)
        left_part.append(ch)
        right_part.append(ch)
        l = chosen_i + 1
        r = chosen_j - 1
        need -= 2

    center = ""
    if need == 1:
        if not want_max:
            for c in range(ALPH):
                i = next_pos[l][c]
                if i != -1 and i <= r:
                    center = chr(c + 97)
                    break
        else:
            for c in range(ALPH-1, -1, -1):
                i = next_pos[l][c]
                if i != -1 and i <= r:
                    center = chr(c + 97)
                    break

    return "".join(left_part) + center + "".join(reversed(right_part))

def main():
    s = str(input())
    n = len(s)

    if n == 1:
        print(s)
        print(s)
        return

    next_pos, prev_pos = build_next_prev(s)
    dp = compute_dp_triangular(s)
    min_pal = reconstruct(s, dp, next_pos, prev_pos, want_max=False)
    max_pal = reconstruct(s, dp, next_pos, prev_pos, want_max=True)
    print(min_pal)
    print(max_pal)

if __name__ == "__main__":
    main()