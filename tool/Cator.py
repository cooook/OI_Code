def C(n, m):
    Ans = 1
    for i in range(1, m + 1):
        Ans *= n - i + 1
    for i in range(1, m + 1):
        Ans /= i;
    return Ans
n = input()
print(C(n * 2, n) - C(n * 2, n - 1))