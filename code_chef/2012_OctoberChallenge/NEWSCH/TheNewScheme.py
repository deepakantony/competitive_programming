# ******************************************************************************
# Problem: The New Scheme
# Link: http://www.codechef.com/OCT12/problems/NEWSCH
# Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
# Solution: Permutation problem. 
# Number of ways to select the a dish for the first day is 4. Number of ways to
# select a dish for second day is 3 till the last one, which should be different
# from the previous one and the first one. So, number of ways to select a dish
# for last day is 2. So the total for this is 4*3*...*3*2 = 4*(3^(n-2))*2. This
# doesn't take into account for the case when the dish on first day and the last
# but one day is same. For this case I can choose from 3 dishes for last day.
# So I need to find the number of ways to schedule scheme for (n-2) days and add
# it. Which is scheme[n] = scheme[n-2] + 4*3^(n-2)*2 
# Solving: scheme[n] = 4*(3^(n-2)+3^(n-4)...)*2
# Note, scheme[1] = 4
# So, scheme[n] = 8*GP(3, 9, (n-3)/2) when n is odd 
# scheme[n] = 8*GP(1, 9, (n-2)/2) when n is even
#                   where the function GP is GP(a, r, n)
# reduces to:
# scheme[n] = 3*(9^((n-1)/2) - 1) when n is odd
#           = 9^(n/2) + 3 when n is even
# ******************************************************************************

# Uncomment this line if the judge supports psyco
# NOTE: psyco is not supported in 2.7 and 3.x+
# import psyco
# psyco.full()

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

modnum = 1000000007

def solveTheNewScheme():
    T = int(raw_input())
    for test in xrange(T):
        N = int(raw_input())
        if N%2 == 1:
            print (3*((pow(9, (N-1)/2, modnum)) - 1)%modnum)%modnum
        else:
            print (pow(9, N/2, modnum) + 3)%modnum

@timeElapsed
def main():
    """ Main controller """
    # solve a problem here
    solveTheNewScheme()

if __name__ == "__main__":
    main()
