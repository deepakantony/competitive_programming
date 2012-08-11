import copy

mod = 1000000007

# initialize the array memo. memo is the dp array that contains number of ways
# we can move from a given location in M steps. At this initalization stage it
# would moving 0 steps. And thus all entries will be initialized to 1.
def initMemo(N, dimensions, memo):
    for dim in xrange(N):
        memo.append([1]*dimensions[dim])

# This function calculates the memo given what the memo was at step M-1. What
# i'm doing here is to calculate the number of ways I can move M steps at every
# location (in every direction from given source) given the number of ways to
# move M-1 steps at every location.
def calculateNextMemo(startLocation, memo):
    prevmemo = copy.deepcopy(memo)
    N = len(startLocation)
    for dim in xrange(N):
        for loc in xrange(len(memo[dim])):
            curValue = 0
            for dimSL, locSL in enumerate(startLocation):
                if dimSL != dim:
                    if locSL-1 >= 0:
                        curValue += prevmemo[dimSL][locSL-1] 
                    if locSL+1 < len(memo[dimSL]):
                        curValue += prevmemo[dimSL][locSL+1] 
                else:
                    if loc-1 >= 0:
                        curValue += prevmemo[dimSL][loc-1]
                    if loc+1 < len(memo[dimSL]):
                        curValue += prevmemo[dimSL][loc+1]
            memo[dim][loc] = curValue%mod

# The idea here is to calculate the number of ways to move within grid in step M
# given the data for step M-1. We don't need to calculate at every location of 
# the grid; it only needs to be calculated in all directions from the source
# location. This mean at most N directions and each dimension being atmost 100.
# So, we keep a 2d array called memo[10][100] and continuosly calculate for 
# every step. Obviously, for step M = 0 we initialize every thing to 1.
def solveGridWalking(N,M,dimensions,startLocation):
    memo = []

    initMemo(N, dimensions, memo)
    for step in xrange(M):
        calculateNextMemo(startLocation, memo)
        print step
        for rowarray in memo:
            print rowarray

    return memo[0][startLocation[0]]

def main():
    T = int(raw_input())
    for test in xrange(T):
        N,M = tuple([int(x) for x in raw_input().split()])
        startLocation = [int(x)-1 for x in raw_input().split()]
        dimensions = [int(x) for x in raw_input().split()]
        print solveGridWalking(N,M,dimensions,startLocation)

if __name__ == "__main__":
    main()
