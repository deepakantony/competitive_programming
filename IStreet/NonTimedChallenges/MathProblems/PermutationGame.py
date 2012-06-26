# Permutation Game : Problem description
# 
# Alice and Bob play the following game:
# 
# 1) They choose a permutation of the first N numbers to begin with.
# 2) They play alternately and Alice plays first.
# 3) In a turn, they can remove any one remaining number from the permutation.
# 4) The game ends when the remaining numbers form an increasing sequence. 
# The person who played the last turn (after which the sequence becomes 
# increasing) wins the game.
# 
# Assuming both play optimally, who wins the game?
# 
# Input:
# The first line contains the number of test cases T. T test cases follow. 
# Each case contains an integer N on the first line, followed by a 
# permutation of the integers 1..N on the second line.
# 
# Output:
# Output T lines, one for each test case, containing "Alice" if Alice wins 
# the game and "Bob" otherwise.
# 
# Constraints:
# 1 <= T <= 100
# 2 <= N <= 15
# The permutation will not be an increasing sequence initially.
# 
# Sample Input:
# 2
# 3
# 1 3 2
# 5
# 5 3 2 1 4
# 
# Sample Output:
# Alice
# Bob
# 
# 
# Explanation: For the first example, Alice can remove the 3 or the 2 to 
# make the sequence increasing and wins the game.
# 
#
# Use the sprague-grundy theorem. Read up on impartial games, mex rule
# etc...
#
import sys

def getMex(myCurGVals):
    mex = 0
    while True:
        if mex in myCurGVals:
            mex += 1
        else:
            return mex

def getNextGrundyIndex(curGrundyIndex, removeNum):
    return curGrundyIndex | (1 << (removeNum-1))

def isSorted(permutation):
    prev = 0
    cur = 1
    for curIndex in xrange(len(permutation)-1):
        if permutation[cur] < permutation[prev]:
            return False

        prev += 1
        cur += 1

    return True


def spragueGrundy(permutation, curGrundyIndex, grundyVals):
    if len(permutation) == 2:
        if permutation[0] > permutation[1]:
            grundyVals[curGrundyIndex] = 1
            return 1
        else:
            grundyVals[curGrundyIndex] = 0
            return 0

    if len(permutation) == 1 or isSorted(permutation):
        grundyVals[curGrundyIndex] = 0
        return 0

    curGrundySet = set()
    for (index, num) in enumerate(permutation):
        nextGrundyIndex = getNextGrundyIndex(curGrundyIndex, num)
        if nextGrundyIndex not in grundyVals:
            newPermutation = permutation[0:index]
            newPermutation.extend(permutation[index+1:])
            spragueGrundy(newPermutation, nextGrundyIndex, grundyVals)
        curGrundySet.add(grundyVals[nextGrundyIndex])

    grundyVals[curGrundyIndex] = getMex(curGrundySet)
    return grundyVals[curGrundyIndex]

def main():
    instream = sys.stdin

    if len(sys.argv) > 1:
        instream = open(sys.argv[1])

    nTests = int(instream.readline())

    for test in xrange(nTests):
        N = int(instream.readline())
        permutation = [ int(x) for x in instream.readline().split() ]
        if spragueGrundy(permutation, 1 << 15, {}) is 0:
            print "Bob"
        else:
            print "Alice"
            

if __name__ == "__main__":
    main()
