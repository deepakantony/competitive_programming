# ******************************************************************************
# Problem: Fierce Battles
# Link: http://www.codechef.com/OCT12/problems/DRGNBOOL
# Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
# Solution: simple; sum up the total for each level and subtract from the 
# sofloats total capacity for that level; in the end sum up all levels with
# positive diff's
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

def solveFierceBattles():
    T = int(raw_input())
    for test in xrange(T):
        N, M = tuple( int(x) for x in raw_input().split() )
        soints = {}
        for ints in xrange(N):
            chakra, level = tuple( int(x) for x in raw_input().split() )
            if level not in soints:
                soints[level] = chakra
            else:
                soints[level] += chakra
        sofloats = {}
        for floats in xrange(M):
            chakra, level = tuple( int(x) for x in raw_input().split() )
            if level not in sofloats:
                sofloats[level] = chakra
            else:
                sofloats[level] += chakra
        res = 0
        for level, chakra in soints.iteritems():

            if chakra < sofloats[level]:
                res += sofloats[level]-chakra
        print res
        

@timeElapsed
def main():
    """ Main controller """
    # solve a problem here
    solveFierceBattles()

if __name__ == "__main__":
    main()
