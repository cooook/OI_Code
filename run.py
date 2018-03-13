import os

cnt = 0;

# os.system("g++ maker.cpp -o maker -Wl,--stack=1024000000");
os.system("g++ A.cpp -o A -Wl,--stack=1024000000");
os.system("g++ bl.cpp -o bl -Wl,--stack=1024000000");

while True:
    os.system("python maker.py");
    os.system("A.exe");
    os.system("bl.exe");
    if os.system("fc tmp.out T1.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);
