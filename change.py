f = open("copy.txt", "r");
out = open(".out", "w");
t = f.read().split('\n');

def Change(x):
    digit = [];
    cnt = 0;
    Ans = 0;
    mul = 1;
    while x:
        Ans <<= 1;
        Ans += (x & 1);
        x >>= 1;
    return Ans; 


for i in range(0, len(t)):
    print >> out, Change(t[i]);
