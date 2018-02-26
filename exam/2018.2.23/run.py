import os

cnt = 0;

os.system("g++ maker.cpp -o maker");
os.system("g++ T3.cpp -o T3");
os.system("g++ bl.cpp -o bl");

while True:
    os.system("maker.exe");
    os.system("T3.exe");
    os.system("bl.exe");
    if os.system("fc bl.out Cooook.out") : 
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "OK! {test_num} test pass!".format(test_num = cnt);