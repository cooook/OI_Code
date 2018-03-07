import os

cnt = 0;

os.system("g++ T2_heap.cpp -o T2_heap");
os.system("g++ T2.cpp -o T2");

while True:
    os.system("python maker.py");
    os.system("T2.exe");
    os.system("T2_heap.exe");
    if os.system("fc bl.out Cooook.out"):
        print "Wrong_Answer!";
        exit();
    cnt += 1;
    print "test {test_num} pass!".format(test_num = cnt);