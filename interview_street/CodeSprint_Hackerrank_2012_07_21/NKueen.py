
N = 30
def canPlace(col, row, kueens, colset):
    for currow, curcol in enumerate(kueens):
        # check if in same diagonal
        if abs(col-row+currow) == curcol:
            return False
        # check if same col
        if col == curcol:
            return False
        # check if knight attack
        if currow+2 == row and abs(curcol-col) == 1:
            return False
        if currow+1 == row and abs(curcol-col) == 2:
            return False
    return True
            


def nKueens(row, kueens, colset):
    if row == N: return True

    for col in xrange(N):
        if canPlace(col, row, kueens, colset):
            kueens.append(col)
            if not nKueens(row+1, kueens, colset):
                kueens.pop()
            else:
                return True
    return False
    

def main():
    print N
    kueens = []
    colset = set()
    nKueens(0, kueens, colset)
    print [x+1 for x in kueens]

if __name__ == "__main__":
    main()
