from random import *
f = open("T3.in", "w"); 


n = 1000;

print >> f, n; 

for i in range(1, n + 1):
    print >> f, randint(1, n),

print >> f, ' '; 

m = 1000;

print >> f, m; 

while m:
    m -= 1;
    l = randint(1, n - 1);
    r = randint(1, n - l);
    print >> f, l, l + r;