# **************************************************************************
# Problem: Bot saves princess
# Link: https://www.hackerrank.com/challenges/saveprincess
# Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
# Solution: just find the manhattan distance between bot and princess
# **************************************************************************

import time
import sys

def timeElapsed(fn):
    """ A time elapsed decorator """
    def wrapper(*args, **kwargs):
        start = time.time()
        res = fn(*args, **kwargs)
        sys.stderr.write("Time Elapsed: %f seconds\n"%(time.time()-start))
        return res
    return wrapper

def getLocOf(c, grid, n):
    for row in range(n):
        for col in range(n):
            if grid[row][col] == c:
                return (col, row)
    return (-1, -1)


def displayPathtoPrincess(n,grid):
    (mx, my) = getLocOf('m', grid, n)
    (px, py) = getLocOf('p', grid, n)

    #print (mx, my)
    #print (px, py)

    if px <= mx: # princess is left of bot
        for _ in range(mx-px): print ("LEFT") 
    if px > mx: # princess is right of bot
        for _ in range(px-mx): print ("RIGHT")
    if py <= my: # princess is top corners
        for _ in range(my-py): print ("UP")
    if py > my: # princess is in bottom corners
        for _ in range(py-my): print ("DOWN") 


@timeElapsed
def main():
    """ Main controller """
    # solve a problem here

    #print all the moves here
    m = int(input())
    grid = [] 
    for i in range(0, m): 
        grid.append(input().strip())

    displayPathtoPrincess(m,grid)

if __name__ == "__main__":
    main()
