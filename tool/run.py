import os

cnt = 0;

os.system("g++ 233.cpp -o 233");
os.system("g++ maker.cpp -o maker");
os.system("g++ bl.cpp -o bl");

while True : 
    os.system("maker");
    os.system("bl.exe");
    os.system("233.exe");
    if os.system("fc bl.out Cooook.out") : 
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);