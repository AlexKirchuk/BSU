with open("input.txt", "r") as fin, open("output.txt", "w") as fout:
    n = int(fin.readline())
    i = 0
    while n:
        if n % 2:
            fout.write(f"{i}\n")
        i += 1
        n //= 2