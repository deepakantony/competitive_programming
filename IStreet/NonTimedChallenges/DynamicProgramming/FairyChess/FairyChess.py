import sys
import copy

mod = 1000000007

# From the original input, this function creates a diamond shaped board, which 
# is double the size.
def initResultBoard(board):
    """Returns the rotated board with integer values in it.

    >>> initResultBoard([".....","...L.", ".P.P.", "P.P..", "..P.."])
    ([[0, 0, 0, 0, 1, 0, 0, 0, 0], [0, 0, 0, 1, 0, 1, 0, 0, 0], [0, 0, 1, 0, 1, 0, 1, 0, 0], [0, 0, 0, 0, 0, 1, 0, 1, 0], [1, 0, 1, 0, 1, 0, 1, 0, 1], [0, 1, 0, 0, 0, 0, 0, 1, 0], [0, 0, 0, 0, 1, 0, 1, 0, 0], [0, 0, 0, 1, 0, 1, 0, 0, 0], [0, 0, 0, 0, 1, 0, 0, 0, 0]], 4, 6)
    """
    resBoard = []
    size = len(board)
    newsize = size*2 - 1
    midway = newsize/2
    # index in diamond
    coldmndi, coldmndj = midway, midway+1
    stepcoli, stepcolj = -1, 1
    starti, startj = 0, 0
    incri, incrj = 1, 0
    row, col = 0, 0
    lastIndex = []
    for x in xrange(newsize):
        lastIndex.append(coldmndj)
        resrow = [0]*newsize
        for y in xrange(coldmndi, coldmndj, 2):

            if board[row][col] == '.':
                resrow[y] = 1
            elif board[row][col] == 'L':
                resrow[y] = 1
                lx, ly = x, y
            row, col = row-1, col+1
        resBoard.append(resrow)
        if coldmndi <= 0:
            stepcoli, stepcolj = (stepcolj, stepcoli)
            starti, startj = (size-1, 0)
            incri, incrj = (0, 1)
        coldmndi += stepcoli
        coldmndj += stepcolj
        starti, startj = (starti+incri, startj + incrj)
        row, col = starti, startj

    
    return (resBoard, lx, ly, lastIndex)

# Identify the location of the starting positon
def getStartingPosition(board):
    for i, row in enumerate(board):
        for j, col in enumerate(row):
            if col == 'L':
                return (i,j)
    raise ValueError("Board does not have L!")

# Calculates the partial sum
def constructSumBoard(board, resBoard):
    size = len(board)
    midway = size/2
    coldmndi, coldmndj = midway, midway+1
    stepcoli, stepcolj = -1, 1

    for x in xrange(size):
        resrow = resBoard[x]
        for y in xrange(coldmndi, size, 2):
            resrow[y] = board[x][y]
            if (x-1) >= 0 and (y-1) >= 0: resrow[y] = (resrow[y] + resBoard[x-1][y-1]) % mod
            if (x-2) >= 0: resrow[y] = (resrow[y] + resBoard[x-2][y]) % mod
            if (y-2) >= 0: resrow[y] = (resrow[y] + resBoard[x][y-2]) % mod
            if (x-2) >= 0 and (y-2) >= 0:
                resrow[y] = (resrow[y] - resBoard[x-2][y-2]) % mod
        if x >= midway:
            coldmndi = 0 if coldmndi == 1 else 1


# old method
def constructSumBoardOld(board):
    res = []
    for i, row in enumerate(board):
        resrow = []
        for j, col in enumerate(row):
            resrow.append(col)
            if j > 0: resrow[j] = (resrow[j] + resrow[j-1]) % mod
            if i > 0: resrow[j] = (resrow[j] + res[i-1][j]) % mod
            if j > 0 and i > 0: resrow[j] = (resrow[j] - res[i-1][j-1]) % mod
        res.append(resrow)
    return res

# Recalculate the board values based on the partial sums
def recalculateResultBoard(origboard, sumboard, S, lastIndex, resBoard):
    prevBoard = copy.deepcopy(resBoard)
    size = len(origboard)
    midway = size/2
    coldmndi, coldmndj = midway, midway+1
    stepcoli, stepcolj = -1, 1

    for x in xrange(size):
        resrow = resBoard[x]
        for y in xrange(coldmndi, coldmndj, 2):
            if origboard[x][y] == 1:
                resrow[y] = sumboard[min(size-1,x+S)][min(size-1, y+S)]
                if x-S-1 >= 0:
                    resrow[y] = (resrow[y] - sumboard[x-S-1][min(size-1, y+S-1)])%mod
                if x-S-2 >= 0:
                    resrow[y] = (resrow[y] - prevBoard[x-S-2][min(size-1, y+S)])%mod
                    
                if y-S-1 >= 0:
                    resrow[y] = (resrow[y] - sumboard[min(size-1, x+S-1)][y-S-1])%mod
                if y-S-2 >= 0:
                    resrow[y] = (resrow[y] - prevBoard[min(size-1, x+S)][y-S-2])%mod

                if x-S-1 >= 0 and y-S-1 >= 0:
                    resrow[y] = (resrow[y] + sumboard[x-S-1][y-S-1])%mod

        if coldmndi <= 0:
            stepcoli, stepcolj = (0, stepcoli)
        coldmndi += stepcoli
        coldmndj += stepcolj

# This is DP solution. The idea is to calculate the number of ways to move from
# the every location at each step. For step 1 it would be the total number of
# positions that can be reached from that location given S. For step 2 it would
# be the sum of these values at every location and so on.
# To do this easily for M steps, at every step we need to calculate the partial
# sum just like we do for the classic maxsum DP problem. Using these values, we
# can calculate the total number of ways at each step in O(N^2) ways. This gives
# us the total complexity at O(MN^2).
# Note that to do this partial sums easily, the board must be rotated to a 
# diamond shape so that our calculation is easy.
def fairyChess(N,S,M,board):
    (origboard, Lx, Ly, lastIndex) = initResultBoard(board)
    resBoard = copy.deepcopy(origboard)
    sumBoard = copy.deepcopy(origboard)
    for step in xrange(M):
        constructSumBoard(resBoard, sumBoard)
        temp = constructSumBoardOld(resBoard)
        for x, rowvals in enumerate(temp):
            #print rowvals
            print sumBoard[x]
                
        #print "Sumboard:", sumBoard
        recalculateResultBoard(origboard, sumBoard, S, lastIndex, resBoard)
        #print "Resboard:", resBoard

    return resBoard[Lx][Ly]
    
def main():
    T = int(raw_input())
    for test in xrange(T):
        N,M,S = tuple( [ int(x) for x in raw_input().split() ] )
        board = []
        for row in xrange(N):
            rowstring = raw_input().strip()
            board.append(rowstring)
        print fairyChess(N,S,M,board)

if __name__ == "__main__":
    main()
