import os

cnt = 0;

os.system("g++ UOJ169.cpp -o UOJ169");
os.system("g++ bl.cpp -o bl");

while True : 
    os.system("python maker.py");
    os.system("bl.exe");
    os.system("UOJ169.exe");
    if os.system("fc bl.out Cooook.out") : 
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);