#!/usr/bin/env python

# Problem originally from: 
# http://www.interviewstreet.com/recruit/challenges/solve/view/4e1491425cf10/4efa2b594f40f

# Obviously this is a brute force

import sys

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


# Returns the product of nth term Arithmetic series from index i to j in the list
def prodOfAS(listOfAS, i, j, n):
    finalValue = 1
    for index in xrange(i,j):
        finalValue *= listOfAS[index][n]

    return finalValue

# Update the value of 'power' for series from index i to j
def update(listOfAS, i, j, val):
    for index in xrange(i,j):
        listOfAS[index].power += val

# query: prints the K and constant value for which the series would become a 
# arithmetic progression; the series is constructed from listOfAS by the product
# of their corresponding terms and calculating the difference between 
# consecutive terms. See the description at the beginning. This function gives 
# out the final answer
def query(listOfAS, i, j):
    # construct the first 3 terms of the series
    a0 = prodOfAS(listOfAS, i, j, 1) # a0 is the 1st term i.e. n=1
    a1 = prodOfAS(listOfAS, i, j, 2)
    a2 = prodOfAS(listOfAS, i, j, 3)
    K = 1

    while (a1-a0) != (a2-a1):
        a0 = a1 - a0
        a1 = a2 - a1
        a2 = prodOfAS(listOfAS, i, j, K+3) - a2
        K += 1

    print "%d %d" % (K, (a1-a0)%1000003)
    

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
