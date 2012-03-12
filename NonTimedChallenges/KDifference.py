#!/usr/bin/env python

# Given N numbers , [N<=10^5] we need to count the total pairs of numbers 
# that have a difference of K. [K>0 and K<1e9]
# 
# Input Format:
# 1st line contains N & K (integers).
# 2nd line contains N numbers of the set. All the N numbers are assured to 
# be distinct.
# Output Format:
# One integer saying the no of pairs of numbers that have a diff K.
# 
# Sample Input #00:
# 5 2
# 1 5 3 4 2
# 
# Sample Output #00:
# 3
#  
# Sample Input #01:
# 10 1
# 363374326 364147530 61825163 1073065718 1281246024 1399469912 428047635 
# 491595254 879792181 1069262793 
#  
# Sample Output #01:
# 0
# 

def main(argv):
    inp = sys.stdin
    out = sys.stdout
    if len(argv) > 1:
        inp = open(argv[1], 'r')
        if len(argv) > 2: out = open(argv[2], 'r')

    (N, K) = tuple([int(x) for x in inp.readline().split()])
    iterator = (int(x) for x in inp.readline().split())
    setOfN = set(iterator)

    totalPairs = 0
    for x in setOfN:
        if (x+K) in setOfN:
            totalPairs += 1

    print totalPairs

    if len(argv) > 1: inp.close()
    if len(argv) > 2: out.close()

if __name__ == "__main__":
    import sys
    main(sys.argv)
