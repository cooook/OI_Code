from os import system
from random import *

f = open("T1.in", "w");

T = randint(1, 400);

print >> f, T; 

while T:
    T -= 1;
    n = randint(1, 100);
    k = randint(1, 100);
    print >> f, n, k;