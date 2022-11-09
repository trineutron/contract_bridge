def hcp(s):
    res = 0
    for c in s:
        if c == 'A':
            res += 4
        elif c == 'K':
            res += 3
        elif c == 'Q':
            res += 2
        elif c == 'J':
            res += 1
    return res


with open('Library.asc', 'rt', encoding='utf-8') as fin:
    data = list(fin)

count = [[0] * 8 for _ in range(41)]
for line in data:
    s, tricks = line.split(':')
    s = s.split()
    for i in range(4):
        totalhcp = hcp(s[i]) + hcp(s[(i + 2) % 4])
        count[totalhcp][0] += 1
        trick = int(tricks[(2 - i) % 4], 16)
        if i % 2 == 0:
            trick = 13 - trick
        for j in range(1, trick - 5):
            count[totalhcp][j] += 1
for i in range(41):
    for j in range(1, 8):
        if count[i][0] == 0:
            break
        count[i][j] /= count[i][0]
    print(f"{i:2d}", end=' ')
    for j in range(1, 8):
        print(f"{count[i][j]:.5f}", end=' ')
    print(count[i][0])
