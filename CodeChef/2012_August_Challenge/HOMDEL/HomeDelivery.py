# Floyd warshall 
def main():
    N = int(raw_input())
    T = []
    for row in xrange(N):
        T.append([int(x) for x in raw_input().split()])
    # find the shortest between each pair.
    for i in xrange(N):
        for j in xrange(N):
            for k in xrange(N):
                T[i][j] = min(T[i][j], T[i][k]+T[k][j])
    M = int(raw_input())
    for scenario in xrange(M):
        S, G, D = tuple([int(x) for x in raw_input().split()])
        timeTaken = T[S][G] + T[G][D]
        timeWasted = max(0, timeTaken-T[S][D])
        print timeTaken, timeWasted

if __name__ == "__main__":
    main()
