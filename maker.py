from random import *


f = open("Cooook.in", "w"); 


n = 50; 
print >> f, n;

test_num = 1;
while test_num <= n:
    r = randint(1, n)
    l = randint(1, r)
    print >> f, l, r;
    test_num += 1;
