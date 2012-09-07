# Problem: Three is Crowd
# Link: http://www.codechef.com/SEP12/problems/CROWD
# Author: deebee
# Solution: 

def hasContiguous1s(n):
    c = 0
    while(n > 0):
        if n % 2 == 1:
            c += 1
            if c == 3: return True
        else: c = 0
        n /= 2

    return False

def dec2bin(n):
    res = ""
    while n > 0:
            res += str(n%2)
            n/=2
    return res[::-1]

def totalContiguos(digits):
    total = 0
    for x in xrange(2**digits):
        if hasContiguous1s(x): 
            total += 1
            print dec2bin(x), 1
        else:
            print dec2bin(x), 0
    print total
    return total

def formulaMethod(n):
    #print n
    if n < 3: return 0
    if n == 3 : return 1
    total = 0
    
    for x in xrange(3, n, 1):
        total += formulaMethod(x)
    return total + (2**(n-3))

def recurranceFormulaMethod(digits):
    print formulaMethod(digits)


def main():
    T = int(raw_input())
    MOD = 1000000007
    for test in xrange(T):
        N = int(raw_input())
        print totalContiguos(N)
#        if N < 3: print 0
#        elif N == 3: print 1
#        else:
#            res = 1
#            for x in xrange(4, N+1):
#                res = (res+2**(x-3)) % MOD
#
#            print res
#
if __name__ == "__main__":
    totalContiguos(7)
    recurranceFormulaMethod(7)
