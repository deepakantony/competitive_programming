import sys

mod = 1000000007

# TODO: add explanation
def initResultBoard(board):
    resBoard = []
    for row in board:
        resrow = []
        for col in row:
            if col == '.' || col == 'L':
                resrow.append(1)
            else:
                resrow.append(0)
        resBoard.append(resrow)
    return resBoard

# TODO: add explanation
def getStartingPosition(board):
    for i, row in enumerate(board):
        for j, col in enumerate(row):
            if col == 'L':
                return (i,j)
    raise ValueError("Board does not have L!")

# TODO: add explanation
def constructSumBoard(board):
    res = []
    for i, row in enumerate(board):
        resrow = []
        for j, col in enumerate(row):
            resrow.append(col)
            if j > 0: resrow[j] = (resrow[j] + resrow[j-1]) % mod
            if i > 0: resrow[j] = (resrow[j] + res[i-1][j]) % mod
            if j > 0 and i > 0: resrow[j] = (resrow[j] - res[i-1][j-1]) % mod
        res.append(resrow)

# TODO: add explanation
def recalculateResultBoard(board, S):
    pass

# TODO: add explanation
def fairyChess(N,S,M,board):
    resBoard = initResultBoard(board)
    (Lx,Ly) = getStartingPosition(board)
    for step in xrange(M):
        sumBoard = constructSumBoard(resBoard)
        resBoard = recalculateResultBoard(sumBoard)
    return resBoard[Lx][Ly]
    
def main():
    pass

if __name__ == "__main__":
    main()
