import os
print "Input the first test number";
test_cnt = input();
print "Input the last test number";
test_all = input();
print "Input the file name"
fullname = raw_input();
name = fullname.split('.');
os.system("g++ " + fullname + " -o " + name);
print "Input the data name"
data_name = raw_input();

while test_cnt <= test_all:
    os.system("name < " + data_name + str(test_cnt) + ".in > Cooook.out");
    if os.system("fc Cooook.out " + data_name + str(test_cnt) + ".out") : 
        print "Wrong_Answer on test {num}".format(num = test_cnt);
    else : 
        print "Test {num} Ac!".format(num = test_cnt);
    test_cnt += 1;

