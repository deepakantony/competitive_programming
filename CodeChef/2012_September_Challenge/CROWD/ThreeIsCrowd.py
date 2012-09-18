# Problem: Three is Crowd
# Link: http://www.codechef.com/SEP12/problems/CROWD
# Author: deebee
# Solution: Forms the series 1, 3, 8, 20, 47, ... This is given by
#     2^N - tribonacci(N+4)

import copy

MOD = 1000000007

class Matrix:
    def __init__(self, size):
        self.size = size
        self.mat = []
        for x in xrange(self.size):
            row = [0] * self.size
            self.mat.append(row)

    def multiply(self, other):
        if other.size != self.size:
            raise ValueError("Cannot multiply matrices")
        res = Matrix(self.size)
        for x in xrange(self.size):
            for y in xrange(self.size):
                for z in xrange(self.size):
                    res.mat[x][y] = (res.mat[x][y] + \
                                         (self.mat[x][z] * \
                                              other.mat[z][y])%MOD)%MOD
        return res

    def exponentiate(self, exp):
        base = copy.deepcopy(self)
        
        res = Matrix(self.size)
        for x in xrange(res.size):
            res.mat[x][x] = 1

        while exp > 0:
            if exp%2 == 1: # odd
                res = res.multiply(base)
            exp >>= 1
            base = base.multiply(base)

        return res

class TribonacciMatrix(Matrix):
    def __init__(self):
        Matrix.__init__(self, 3)
        self.mat[0][0] = self.mat[0][1] = self.mat[0][2] = 1
        self.mat[1][0] = self.mat[2][1] = 1

    def tribonacciNumber(self, n):
        if n < 3: return 0
        if n == 3: return 1
        sqmat = self.exponentiate(n-2)
        return sqmat.mat[0][2]

def tribonacciSeries(N):
    tribonacci = TribonacciMatrix()
    for x in xrange(1,N,1):
        print tribonacci.tribonacciNumber(x)

def contiguosTriple1s(N):
    tribonacci = TribonacciMatrix()
    return (pow(2, N, MOD) - tribonacci.tribonacciNumber(N+4))%MOD

def contiguosTriple1sSeries(N):
    for x in xrange(1, N, 1):
        print contiguosTriple1s(x)
    

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
#            print dec2bin(x), 1
#        else:
#            print dec2bin(x), 0
#    print total
    return total

def formulaMethod(n):
    #print n
    if n < 3: return 0
    if n == 3 : return 1
    total = 0
    
    for x in xrange(3, n, 1):
        total += formulaMethod(x)
    return total + (2**(n-3))

def recurranceFormulaMethod(n):
    if n < 3: return 0
    if n == 3: return 1
    return recurranceFormulaMethod(n-2) + \
        recurranceFormulaMethod(n-2) + \
        recurranceFormulaMethod(n-3) + (2**(n-3))


def main():
    T = int(raw_input())
    MOD = 1000000007
    for test in xrange(T):
        N = int(raw_input())
        print contiguosTriple1s(N)

 
if __name__ == "__main__":
    main()
    
