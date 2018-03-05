from os import system
from random import * 

f = open("Cooook.in", "w");

n = 100;
m = 100;

print >> f, n, m;

i = 1;
while i <= n:
    print >> f, randint(-1000, 1000),
    i += 1;

print >> f, '\n', 

i = 1;
while i <= m:
    opt = randint(1, 4);
    l = randint(1, n);
    r = randint(1, n);
    if l > r:
        l ^= r;
        r ^= l;
        l ^= r; 
    if opt <= 2:
        print >> f, opt, l, r, randint(-1000, 1000); 
    else:
        print >> f, opt, l, r; 
    i += 1;
f.close();