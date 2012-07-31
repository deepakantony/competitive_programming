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
    nWays = []
    for i in xrange(N):
        nWays.append([0]*dimension[i])
        memo = [[1]*dimension[i]]
        for j in xrange(M):
            memo.append([0]*dimension[i])
            for pos in xrange(dimension[i]):
                val = 0
                if pos-1 >= 0: val += memo[j][pos-1]
                if pos+1 < dimension[i]: val += memo[j][pos+1]
                memo[j+1][pos] = val%mod
            nWays[i][j] = memo[j+1][startLocation[i]]

    memo = [[0]*M]
    for step in xrange(M):
        val = 0
        for k in xrange(step+1):
            val = (val + nWays[0][step-k]) % mod
            
        memo[0][step] = val

    for dim in xrange(1, N):
        memo.append([0]*M)
        for step in xrange(M):
            val = 0
            for k in xrange(step+1):
                val = (val + ((memo[dim-1][k] * nWays[dim][step-k])%mod
                              * ncr[step][step-k])%mod)%mod
            memo[dim][step] = val

    return memo[N-1][M-1]

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
