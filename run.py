import os

cnt = 0;

os.system("g++ T3_bl.cpp -o T3_bl -O2");
os.system("g++ T3_maker.cpp -o T3_maker -O2");
os.system("g++ T3.cpp -o T3 -O2");

while True:
    os.system("T3_maker");
    os.system("T3_bl.exe");
    os.system("T3.exe");
    if os.system("fc T3.out Cooook.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);
