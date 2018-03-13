from os import system

test_name = raw_input("data_name=");
test_num = int(raw_input("data_num="));
cpp_num = raw_input("file_name=");
system("g++ " + cpp_num + ".cpp -o " + cpp_num + " -Wl,--stack=1024000000 -O2");
system("touch tmp_out.out");
i = 1;
while i <= test_num:
	system(cpp_num + "< " + test_name + str(i) + ".in > tmp_out.out");
	if system("diff -B -b tmp_out.out " + test_name + str(i) + ".out"):
		print "Wrong_Answer %d test" % i;
	else:
		print "Ac! %d test" % i; 
	i += 1;

system("rm tmp_out.out");