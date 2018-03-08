import os

cnt = 0;

os.system("g++ BZOJ3711.cpp -o BZOJ3711");
os.system("g++ Druzyny.cpp -o Druzyny");

while True:
    os.system("python maker.py");
    os.system("Druzyny.exe");
    os.system("BZOJ3711.exe");
    if os.system("fc wq.out Cooook.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);