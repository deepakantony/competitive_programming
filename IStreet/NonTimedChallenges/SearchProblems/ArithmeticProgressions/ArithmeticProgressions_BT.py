#!/usr/bin/env python

# Problem originally from: 
# http://www.interviewstreet.com/recruit/challenges/solve/view/4e1491425cf10/4efa2b594f40f

# Obviously this is a brute force

import sys
import math

# a structure for holding arithmetic series
class AS:
    def __init__(self, firstTerm, diff, power):
        self.firstTerm = firstTerm
        self.diff = diff
        self.power = power
    def __getitem__(self, key):
        return (self.firstTerm + (key-1)*self.diff) ** self.power
    def __str__(self):
        return str((self.firstTerm, self.diff, self.power))

# Update the value of 'power' for series from index i to j
def update(listOfAS, i, j, val):
    for index in xrange(i,j):
        listOfAS[index].power += val

# query: prints the K and constant value for which the series would become a 
# K = pi+...+pj
# V = K! * di^pi * ... * di^pj
def query(listOfAS, i, j):
    K = 0
    V = 1
    MOD = 1000003
    for index in xrange(i, j):
        K += listOfAS[index].power
        V = (V * pow(listOfAS[index].diff, listOfAS[index].power, MOD)) % MOD
    V2 = (V*math.factorial(K)%MOD)%MOD

    print K, V2, math.factorial(K)%MOD, V
    

# main function
def main(argv):
    inp = sys.stdin
    out = sys.stdout
    if len(argv) > 1:
        inp = open(argv[1], 'r')
        if len(argv) > 2: out = open(argv[2], 'r')

    # read the number of AP's
    nAP = int(inp.readline())
    # list of arithmetic series
    listAS = []
    for x in xrange(nAP):
        (firstItem, diff, power) = tuple([ int(y) for y in inp.readline().split()])
        aSeries = AS(firstItem, diff, power)
        listAS.append(aSeries)

    # read the number of operations
    nOP = int(inp.readline())
    for x in xrange(nOP):
        inpStr = inp.readline().rstrip()
        if inpStr[0] == '0':
            (dummy, startIndex, lastIndex) = tuple([int(y) for y in inpStr.split()])
            query(listAS, startIndex-1, lastIndex)
        else:
            (dummy, startIndex, lastIndex, value) = tuple([int(y) for y in inpStr.split()])
            update(listAS, startIndex-1, lastIndex, value)

    if len(argv) > 1: inp.close()
    if len(argv) > 2: out.close()

if __name__ == "__main__":
    main(sys.argv)
