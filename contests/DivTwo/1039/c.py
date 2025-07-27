def can_reach(b):
    min_val = b[0]
    for i in range(len(b) - 1):
        if b[i] > b[i + 1]:
            if b[i + 1] < min_val:
                return "NO"
        min_val = min(min_val, b[i + 1])
    return "YES"

t = int(input())
for _ in range(t):
    n = int(input())
    b = list(map(int, input().split()))
    print(can_reach(b))
