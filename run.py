import os

cnt = 0;

os.system("g++ maker.cpp -o maker -Wl,--stack=1024000000");
os.system("g++ T2.cpp -o T2 -Wl,--stack=1024000000");
os.system("g++ tmp.cpp -o tmp -Wl,--stack=1024000000");

while True:
    os.system("maker.exe");
    os.system("T2.exe");
    os.system("tmp.exe");
    if os.system("fc bl.out Cooook.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);
