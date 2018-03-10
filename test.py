f = open("test.out", "w");
ret = []; 

def change(x):
    digit = [];
    while x:
        digit.append(x & 1);
        x >>= 1;
    Ans = 0;
    for x in range(0, len(digit)):
        Ans += digit[x] * 10 ** x;
    return Ans;

def Judge(x):
    digit1 = [];
    digit2 = []; 
    tmp = x;
    while tmp:
        digit1.append(tmp % 10);
        tmp /= 10;
    tmp = x;
    while tmp:
        digit2.append(tmp & 1);
        tmp >>= 1;
    for i in range(0, len(digit1)):
        if digit1[i] != digit2[i]:
            return False;
    ret.append(x); 
    print >> f, x; 
    return True;

Ans = 1;
print >> f, 1; 
ret.append(1); 
i = 0;
while Ans <= 6486:
    Ans += Judge(change(ret[i] * 10));
    Ans += Judge(change(ret[i] * 10 + 1));
    i += 1;

f.close(); 