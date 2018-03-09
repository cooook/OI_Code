import os

cnt = 0;

os.system("g++ std.cpp -o std -O2");
os.system("g++ BZOJ3716.cpp -o BZOJ3716 -O2");

while True:
    os.system("python maker.py");
    os.system("BZOJ3716.exe");
    os.system("std.exe");
    if os.system("fc std.out Cooook.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);
