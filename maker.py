from random import *


f = open("Cooook.in", "w"); 


n = 10; 
m = randint(1, n); 
Max = 5; 
w = randint(1, Max);
h = randint(1, Max); 
print >> f, n, m, '\n', w, h;

test_num = 1;
while test_num <= n + m:
    print >> f, randint(-Max, Max), randint(-Max, Max), randint(1, Max);
    test_num += 1; 