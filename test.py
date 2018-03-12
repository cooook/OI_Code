n, m = raw_input().split(' ');
n = int(n);
m = int(m);
if ((n == 1) & (m == 1)):
    print 1;
elif (n == 1):
    print m - 2;
elif (m == 1):
    print n - 2;
else :
    print n * m - 2 * (n - 1) - 2 * (m - 1);