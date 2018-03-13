from os import *

file_name = raw_input("Input want to rename file ");
re_name = raw_input("Input New name ");
cnt = int(raw_input("Input Number of file "));

i = 1;
while i <= cnt:
	system("rename " + file_name + str(i) + ".* " + re_name + str(i) + ".*");
	i += 1; 