k = input()
n = input()
l = 0
r = n
Ans = 0;

while l <= r:
    mid = l + r >> 1
    if mid ** k <= n:
        Ans = mid
        l = mid + 1
    else:
        r = mid - 1

print Ans; 
