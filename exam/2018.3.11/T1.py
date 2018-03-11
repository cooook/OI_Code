out = open("table.out", "w"); 
f = [];
power = []; 
now = 1;
 
for i in range(0, 150):
    power.append(now);
    f.append(range(now, now + 1));
    now *= 10; 

for i in range(0, len(f)):
    for j in range(0, len(f[i])):
        for k in range(i + 1, 150):
            if f[i][j] >> k & 1:
                break;
            f[k].append(power[k] + f[i][j]);

g = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '{', '}', '|', ':', ';', '<', '>', '?', '~', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '`', '/', '\\', '.', '_', '=', ];

size = len(g); 

def Change(x):
    tmp = x;
    mul = 1;
    Ans = 0;
    while tmp:
        Ans += (tmp % 10) * mul;
        mul <<= 1;
        tmp /= 10;
    x = Ans; 
    while x:
        print >> out, g[x % size],
        x /= size;
    print >> out, '\n',


for i in range(0, len(f)):
    for j in range(0, len(f[i])):
        # Change(f[i][j]);
        print >> out, f[i][j]; 