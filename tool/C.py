n = input()
m = input()
Ans = 1
for i in range(n - m + 1,n + 1):
    Ans = Ans * i;
for i in range(1,m+1):
    Ans = Ans / i;
print(Ans);