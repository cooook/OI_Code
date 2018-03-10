out = open("table.out", "w"); 
f = [];
power = []; 
now = 1;
 
for i in range(0, 151):
    power.append(now);
    f.append(range(now, now + 1));
    now *= 10; 

for i in range(0, len(f)):
    for j in range(0, len(f[i])):
        for k in range(i + 1, 151):
            if f[i][j] >> k & 1:
                break;
            f[k].append(power[k] + f[i][j]);

g = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')'];

def Change(x):
    print >> out, '\"', 
    while x:
        print >> out, g[x % 46],
        x /= 46;
    print >> out, '\",\n',


for i in range(0, len(f)):
    for j in range(0, len(f[i])):
        Change(f[i][j]);