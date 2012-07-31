mod = 1000000007

ncr = []
def initNCR(N):
    global ncr
    ncr = []
    for n in xrange(N+1):
        ncr.append([1]*(N+1))
        ncr[n][0] = 1
    
    for n in xrange(2, N+1):
        for r in xrange(1, n+1):
            ncr[n][r] = (ncr[n-1][r-1] + ncr[n-1][r])%mod

def solveGridWalking(N,M,dimension,startLocation):
    # For dimension i, identify the number of ways I can move j steps in that
    # dimension.
    nWays = [[1]*(M+1)]
    for i in xrange(1, N+1):
        nWays.append([1]*(M+1))
        memo = [[1]*dimension[i-1]]
        for j in xrange(1, M+1):
            memo.append([0]*dimension[i-1])
            for pos in xrange(dimension[i-1]):
                val = 0
                if pos-1 >= 0: val += memo[j-1][pos-1]
                if pos+1 < dimension[i-1]: val += memo[j-1][pos+1]
                memo[j][pos] = val%mod
            nWays[i][j] = memo[j][startLocation[i-1]]

    memo = [[1]*(M+1)]
    for dim in xrange(1, N+1):
        memo.append([1]*(M+1))
        for step in xrange(1, M+1):
            val = 0
            for k in xrange(step+1):
                val = (val + ((memo[dim-1][k] * nWays[dim][step-k])%mod
                              * ncr[step][step-k])%mod)%mod
                print val
            memo[dim][step] = val
    print memo
    return memo[N][M]

def main():
    initNCR(300)
    T = int(raw_input())
    for test in xrange(T):
        N,M = tuple([int(x) for x in raw_input().split()])
        startLocation = [int(x)-1 for x in raw_input().split()]
        dimensions = [int(x) for x in raw_input().split()]
        print solveGridWalking(N,M,dimensions,startLocation)

if __name__ == "__main__":
    main()
