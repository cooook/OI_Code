from random import *
f = open("T1.in", "w")
n = 5;
print >> f, n;

for i in range(1, n + 1):
	print >> f, randint(1, n);

for i in range(2, n + 1):
	print >> f, randint(1, i - 1), i;