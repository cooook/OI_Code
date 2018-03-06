from os import system
from random import * 

f = open("Cooook.in", "w");

n = 100;
m = 100;
data_mx = 10;

print >> f, n;

i = 1;
while i <= n:
    print >> f, randint(-data_mx, data_mx),
    i += 1;
print >> f, '\n', 

print >> f, m; 


i = 1;
while i <= m:
    opt = randint(1, 6);
    l = randint(1, n);
    r = randint(1, n);
    if l > r:
        l ^= r;
        r ^= l;
        l ^= r; 
    if opt <= 3:
        print >> f, opt, l, r, randint(-data_mx, data_mx);
    else :
        print >> f, opt, l, r; 
    i += 1;
f.close();