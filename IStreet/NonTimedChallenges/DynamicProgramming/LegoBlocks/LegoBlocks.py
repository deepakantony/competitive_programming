import sys
import time

mod = 1000000007
singleRow = []
allrow = []

def preCalculate():
    global singleRow
    global allrow
    # First calculate how many ways can we build a wall with just one row,
    # including breakable ones.
    M = 1000
    singleRow = [0]*M
    for x in range(min(4,M)): singleRow[x] = 1
    for x in range(1, M):
        for i in range(min(4,x)):
            singleRow[x] = (singleRow[x] + singleRow[x-1-i])% mod

    # Now calculate the number of ways in which we can build the wall with N
    # rows. This is calculated by x^N, where x is the number of ways we can build
    # a wall in single row. This includes breakable ones.
    for N in xrange(1000):
        row = []
        for x in singleRow:
            row.append(pow(x,N+1,mod))
        allrow.append(row)


def unbreakableLegoBlocks(N,M):

    # Now we need to subtract from this, the number of ways to create breakable
    # walls. So, for each wall of width M, we have total number of ways to 
    # create a wall with height N; this is done with the observation that, to
    # build a wall with size i < M, we have nrow[i] ways to do it and also to
    # build a wall with size M-i we have nrow[M-i] ways to do it. Totally, a 
    # wall which can be split at i can be created in nrow[i]*nrow[M-i] ways.
    # So for every i < M subtract nrow[i]*nrow[M-i] from it to get the number
    # of ways to build unbreakable wall.
    memo = []
    nrow = allrow[N-1]

    for index in xrange(M):
        x = nrow[index]
        memo.append(x)
        for i in range(index):
            memo[index] = (memo[index] - (memo[i]*nrow[index-i-1])%mod)%mod

    return memo[M-1]

def main():
    start = time.clock()
    preCalculate()
    T = int(raw_input())
    for test in xrange(T):
        N,M = tuple([int(x) for x in raw_input().split()])
        print unbreakableLegoBlocks(N,M)
    print >> sys.stderr, time.clock()-start, "seconds"

if __name__ == "__main__":
    main()
