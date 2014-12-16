# ***************************************************************************
# Problem: multiples of 3 and 5
# Link: https://www.hackerrank.com/contests/projecteuler/challenges/euler001
# Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
# Solution: derive the formula to find sum of N multiples of a number
# ***************************************************************************

import time
import sys

def timeElapsed(fn):
    """ A time elapsed decorator """
    def wrapper(*args, **kwargs):
        start = time.time()
        res = fn(*args, **kwargs)
        sys.stderr.write("Time Elapsed: %f seconds\n"%(time.time()-start))
        return res
    return wrapper

def sum_of_n_integers(n):
    return n*(n+1)//2

@timeElapsed
def main():
    """ Main controller """
    # solve a problem here
    T = int(input().strip())
    for test in range(T):
        N = int(input().strip())
        N = N-1
        sum = 0
        sum += 3*sum_of_n_integers(N//3)
        sum += 5*sum_of_n_integers(N//5)
        sum -= 15*sum_of_n_integers(N//15)
        print (sum)

if __name__ == "__main__":
    main()
