import os
import math

# read input and implement a O(M*log(M))
def main():
    T = int(raw_input())
    for test in xrange(T):
        N, M = tuple([ int(x) for x in raw_input().split()])
        mUpdates = [(N, 0)]
        # just store the range updates since the changes happend only at the 
        # ends. 
        for update in xrange(M):
            w, x, y, z = tuple([ int(a) for a in raw_input().split()])
            if w == 2: z = -z

            mUpdates.append(tuple([x-1, z]))
            mUpdates.append(tuple([y, -z]))

        mUpdates.sort()

        i = 0 # curIndex
        a_i = 1
        d_i_1 = 0
        maxSoFar = -float('inf')
        minSoFar = float('inf')
        for cur in mUpdates:
            nexti = cur[0]
            if nexti != i:
                maxSoFar = max(maxSoFar, a_i+nexti-i-1)
                minSoFar = min(minSoFar, a_i)
                #print maxSoFar, minSoFar
                a_i = a_i+nexti-i
            a_i += cur[1]
            i = nexti

        print maxSoFar-minSoFar

if __name__ == "__main__":
    main()

