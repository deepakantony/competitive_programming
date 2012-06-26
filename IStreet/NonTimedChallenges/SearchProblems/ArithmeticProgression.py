#!/usr/bin/env python

# Problem originally from: 
# http://www.interviewstreet.com/recruit/challenges/solve/view/4e1491425cf10/4efa2b594f40f
#
# Arithmetic Progressions (35 points)
# Let F(a,d) denote an arithmetic progression (AP) with first term 'a' and common 
# difference 'd'. i.e  F(a,d) denotes an infinite AP => a, a+d, a+2d, a+3d,... You 
# are given 'n' APs => F(a1,d1), F(a2,d2), F(a3,d3),... F(an,dn). Let 
# G(a1,a2,... an,d1,d2,... dn) denote the sequence obtained by multiplying the 'n' 
# APs.
# 
# Multiplication of 2 sequences is defined as follows: Let the terms of the first 
# sequence be A1, A2, Am, and terms of the second sequence be B1, B2,... Bm. The 
# sequence obtained by multiplying these two sequences is: A1*B1, A2*B2,... Am*Bm. 
# We also give the definition for the kth difference of a sequence. If 
# A1, A2,... Am,... be the terms of a sequence, then the terms of the 1st 
# difference of this sequence are given by A2-A1, A3-A2,... Am-Am-1,... In 
# general, if A1, A2,... Am,... be the terms of the kth difference of a sequence, 
# then the terms of the k+1th difference are given by A2-A1, A3-A2,... Am-Am-1,... 
# We say that the kth difference of a sequence is a constant, if all the terms of 
# the kth difference are equal.
# 
# Let F'(a,d,p) be a sequence defined as => ap, (a+d)p, (a+2d)p,... Similarly, 
# G'(a1,a2,... an,d1,d2,... dn,p1,p2,... pn) is defined as => product of 
# F'(a1,d1,p1), F'(a2,d2,p2),... F'(an,dn,pn). Now, your task is to find the 
# smallest 'k' for which the kth difference of the sequence G' is a constant. You 
# are also required to find this constant value.
#  
# You will be given many operations. Each operation is of one of the 2 forms:
# 1.) 0 i j => 0 indicates a query (1<=i<=j<=n).You are required to find the 
# smallest 'k' for which the  kth difference of 
# G'(ai,ai+1,... aj,di,di+1,... dj,pi,pi+1,... pj) is a constant. You should also 
# output this constant value.
# 2.) 1 i j v => 1 indicates an update (1<=i<=j<=n). For all i<=k<=j, we update 
# pk = pk+v.
# 
# Input:
# The first line of input contains a single integer 'n', denoting the number of 
# APs. Each of the next 'n' lines consists of 3 integers ai, di, pi (1<=i<=n). The 
# next line consists of a single integer 'q', denoting the number of operations. 
# Each of the next 'q' lines consist of one of the two operations mentioned above.
#  
# Output:
# For each query, output a single line containing 2 space separated integers 'K' 
# and 'V'. 'K' is the least value for which the Kth difference of the required 
# sequence is a constant. 'V' is the value of this constant. Since 'V' might be 
# large, output the value of 'V' modulo 1000003.
#  
# Note: 'K' will always be such that it fits into a signed 64-bit integer. All 
# indices for query and update are 1-based. Do not take modulo 1000003 for 'K'.
#  
# Constraints:
# 1<=n<=100000
# 1<=ai, di, pi<=10000
# 1<=q<=100000
# For updates of the form "1 i j v", 1 <= v <= 10000
#  
# Sample Input:
# 2
# 1 2 1
# 5 3 1
# 3
# 0 1 2
# 1 1 1 1
# 0 1 1
# 
# Sample Output:
# 2 12
# 2 8
# 
# Explanation:
# The first sequence given in the input is => 1, 3, 5, 7, 9,...
# The second sequence given in the input is => 5, 8, 11, 14, 17,...
# 
# For the first query operation, we have to consider the product of these two 
# sequences:
# => 1*5, 3*8, 5*11, 7*14, 9*17,...
# => 5, 24, 55, 98, 153,...
# First difference is => 19, 31, 43, 55,...
# Second difference is => 12, 12, 12,... This is a constant and hence the output 
# is "2 12".
# 
# After the update operation "1 1 1 1", the first sequence becomes => 12, 32, 52, 
# 72, 92,... 
# i.e => 1, 9, 25, 49, 81,...
# For the second query, we consider only the first sequence => 1, 9, 25, 49, 81,...
# First difference is => 8, 16, 24, 32,...
# Second difference is => 8, 8, 8,... This is a constant and hence the output is 
# "2 8"

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
