from heapq import *

def checkio(land_map):
    if len(land_map) == 0 : return 0
    last_row = len(land_map)-1
    pq = []
    dist = dict()
    
    # initialize the pq with sources first
    for col,d in enumerate( land_map[0] ):
        dist[(0,col)] = d
        heappush(pq, (d,0,col))
        
    while pq:
        d,row,col = heappop(pq)
        if d > dist[(row,col)]: continue

        for n_row, n_col in [(row,col-1),(row,col+1),(row+1,col),(row-1,col)]:
            if n_row >= 0 <= n_col and n_row <= last_row and n_col < len(land_map[0]):
                n_d = d + land_map[n_row][n_col]
                if (n_row,n_col) not in dist or dist[(n_row,n_col)] > n_d:
                    dist[(n_row,n_col)] = n_d
                    heappush(pq, (n_d,n_row,n_col))

    # return the minimum distance to the last row
    return  min( dist[k] for k in dist if k[0] == last_row )

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio([[1, 1, 1, 1, 0, 1, 1],
                    [1, 1, 1, 1, 0, 0, 1],
                    [1, 1, 1, 1, 1, 0, 1],
                    [1, 1, 0, 1, 1, 0, 1],
                    [1, 1, 0, 1, 1, 1, 1],
                    [1, 0, 0, 1, 1, 1, 1],
                    [1, 0, 1, 1, 1, 1, 1]]) == 2, "1st example"
    assert checkio([[0, 0, 0, 0, 0, 0, 0],
                    [1, 1, 1, 1, 1, 1, 1],
                    [1, 1, 1, 1, 1, 1, 1],
                    [1, 1, 1, 1, 1, 1, 1],
                    [1, 1, 0, 1, 0, 1, 1],
                    [1, 0, 0, 0, 0, 0, 1],
                    [0, 0, 0, 0, 0, 0, 0]]) == 3, "2nd example"
    assert checkio([[1, 1, 1, 1, 1, 0, 1, 1],
                    [1, 0, 1, 1, 1, 0, 1, 1],
                    [1, 0, 1, 0, 1, 0, 1, 0],
                    [1, 0, 1, 1, 1, 0, 1, 1],
                    [0, 0, 1, 1, 0, 0, 0, 0],
                    [1, 0, 1, 1, 1, 1, 1, 1],
                    [1, 0, 1, 1, 1, 1, 1, 1],
                    [1, 1, 1, 0, 1, 1, 1, 1]]) == 2, "3rd example"
    assert checkio([[0,1,1,1,1,1,1,1],
                    [0,1,1,1,1,1,1,1],
                    [0,0,0,0,0,0,0,1],
                    [1,1,1,1,1,1,0,1],
                    [1,1,0,0,0,1,0,0],
                    [0,0,0,1,0,1,1,0],
                    [0,1,1,1,0,0,0,0]]) == 0, "4th example"
    assert checkio([[0,1,1,1,1,1,1,1],
                    [0,1,1,1,1,0,0,0],
                    [0,0,0,0,0,0,1,0],
                    [1,1,1,1,1,1,1,0],
                    [1,1,0,0,0,1,1,0],
                    [0,0,0,1,0,1,1,0],
                    [0,1,1,1,0,0,0,0]]) == 0, "5th example"
