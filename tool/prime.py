for i in range(2,10000):
    p = 0;
    for j in range(2,i):
        if (i % j == 0):p = 1;
    if (p == 0): print(i)
