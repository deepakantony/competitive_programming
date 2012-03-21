#!/usr/bin/env python

# A number is called lucky if the sum of its digits, as well as the sum of the 
# squares of its digits is a prime number. How many numbers between A and B are 
# lucky?
# Input:
# The first line contains the number of test cases T. Each of the next T lines 
# contains two integers, A and B.
# Output:
# Output T lines, one for each case containing the required answer for the 
# corresponding case.
# 
# Constraints:
# 1 <= T <= 10000
# 1 <= A <= B <= 10^18
# Sample Input:
# 2
# 1 20
# 120 130
# Sample Output:
# 4
# 1
# Explanation:
# For the first case, the lucky numbers are 11, 12, 14, 16.
# For the second case, the only lucky number is 120.

import sys
import time

maxSize = 9*9*18 + 2
primes = [-1] * maxSize

def initPrime():
    primes[0] = primes[1] = 0
    index = 2
    while index < maxSize:
        primes[index] = 1
        index2 = index+index
        while index2 < maxSize:
            primes[index2] = 0
            index2 += index
        while index < maxSize and primes[index] != -1:
            index += 1

def isPrime(num):
    return (True if (num < maxSize and primes[num] == 1) else False)

def sumAndSquareSum(num):
    digsSum = 0
    digsSquareSum = 0
    while(num > 0):
        digit = num%10
        digsSum += digit
        digsSquareSum += digit*digit
        num /= 10

    return (digsSum, digsSquareSum)

def isLuckyNum(num):
    (digsSum, digsSquareSum) = sumAndSquareSum(num)
    return (True if isPrime(digsSum) and isPrime(digsSquareSum) else False)
        

def main(argv):
    inp = sys.stdin
    out = sys.stdout
    if len(argv) > 1:
        inp = open(argv[1], 'r')
        if len(argv) > 2:
            out = open(argv[2], 'w')

    start = time.time()

    initPrime()

    nTests = int(inp.readline())
    for x in xrange(0, nTests):
        (A,B) = tuple([int(x) for x in inp.readline().split()])
        luckyNums = 0
        for num in xrange(A,B):
            if isLuckyNum(num):
                luckyNums += 1
        print luckyNums

    if len(argv) > 1:
        inp.close()
        print "Elapsed time: %d" % (time.time()-start)
        if len(argv) > 2:
            out.close()

if __name__ == "__main__":
    main(sys.argv)
