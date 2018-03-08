k = input()
n = input()
l = 0
r = 1
Ans = 0;

while r ** k <= n:
    l = r;
    r = r * 2; 

while l <= r:
    mid = l + r >> 1
    if mid ** k <= n:
        Ans = mid
        l = mid + 1
    else:
        r = mid - 1

print Ans; 
