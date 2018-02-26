n = input()
if (n == 1):
    print(1)
for i in range(2,n + 1):    
    while (n % i == 0):
        print(i)
        n /= i
