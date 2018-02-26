import os

i = 13

while i <= 20 : 
    os.system("maker > easy_problem" + str(i) + ".in");
    os.system("std < easy_problem" + str(i) + ".in > easy_problem" + str(i) + ".out");
    i += 1;