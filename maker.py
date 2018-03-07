from random import *


f = open("Cooook.in", "w"); 


n = 1000;
k = randint(1, n);
max_data = 1e5; 

print >> f, n, k;

for i in range(1, n + 1):
    print >> f, randint(1, max_data),

print >> f, "\n",


for i in range(2, n + 1):
    print >> f, randint(1, i - 1), i;