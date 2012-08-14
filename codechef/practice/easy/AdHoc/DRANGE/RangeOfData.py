import os

# read input and implement a O(M*log(M))
def main():
    T = int(raw_input())
    for test in xrange(T):
        N, M = tuple([ int(x) for x in raw_input().split()])
        mUpdates = [(1, 1), (N, 0)]
        # just store the range updates since the changes happend only at the 
        # ends. 
        for update in xrange(M):
            w, x, y, z = tuple([ int(a) for a in raw_input().split()])
            if w == 2: z = -z
            mUpdates.append(tuple(x, z))
            mUpdates.append(tuple(y, -z))

        sorted(mUpdates)
        

if __name__ == "__main__":
    main()
