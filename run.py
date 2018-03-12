import os

cnt = 0;

# os.system("g++ maker.cpp -o maker -Wl,--stack=1024000000");
os.system("g++ T3.cpp -o T3 -Wl,--stack=1024000000");
os.system("g++ T3_bl.cpp -o T3_bl -Wl,--stack=1024000000");

while True:
    os.system("python T3_maker.py");
    os.system("T3.exe");
    os.system("T3_bl.exe");
    if os.system("fc bl.out T3.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);
