from os import system
from time import clock


test_id = 1;

system("g++ T2.cpp -o T2 -O2 -Wl,--stack=1024000000 -std=c++11")

clock(); 

last = clock(); 

while test_id <= 88:
    system("T2.exe < " + str(test_id) + ".in > Cooook.out");
    if (clock() - last >= 2):
        print "TLE on test %d" % test_id; 
    if system("fc Cooook.out " + str(test_id) + ".out"):
        print "Wrong_Answer on test %d" % test_id;
        exit();
    print "test %d Ac!" % test_id; 
    test_id += 1;
    last = clock();

print "All right..."