class disjoint_set:
    def __init__(self):
        self.parent = {}
        self.rank = {}
        self.count = 0
        self.length = {}

    def add( self, x ):
        if self.exist(x): return # set contains x
        self.parent[x] = x
        self.rank[x] = 0
        self.count += 1
        self.length[x] = 1

    def exist( self, x ):
        return x in self.parent

    def find( self, x ): 
        if not self.exist(x): return None
        if self.parent[x] == x: return x
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union( self, x, y ):
        if not self.exist(x) or not self.exist(y): return

        px,py = self.find(x), self.find(y)
        if px != py:
            if self.rank[x] > self.rank[y]:
                self.parent[y] = x
                self.length[px] += self.length[py]
                self.length.pop(py)
            else:
                self.parent[x] = y
                if self.rank[x] == self.rank[y]: self.rank[y] += 1
                self.length[py] += self.length[px]
                self.length.pop(px)
    

def checkio(land_map):
    islands = disjoint_set()
    neighbors = { (-1,0), (0,-1), (-1,-1), (-1, 1) }
    for row, row_sizes in enumerate(land_map):
        for col, size in enumerate(row_sizes):
            if size:
                islands.add((row,col))
                for n1,n2 in neighbors:
                    r,c = row+n1,col+n2
                    if 0<=r and 0<=c<len(row_sizes) and land_map[r][c]:
                        islands.union((row,col),(r,c))

    islands_sizes = sorted( [ islands.length[x] for x in islands.length ] )
    return islands_sizes

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio([[0, 0, 0, 0, 0],
                    [0, 0, 1, 1, 0],
                    [0, 0, 0, 1, 0],
                    [0, 1, 0, 0, 0],
                    [0, 0, 0, 0, 0]]) == [1, 3], "1st example"
    assert checkio([[0, 0, 0, 0, 0],
                    [0, 0, 1, 1, 0],
                    [0, 0, 0, 1, 0],
                    [0, 1, 1, 0, 0]]) == [5], "2nd example"
    assert checkio([[0, 0, 0, 0, 0, 0],
                    [1, 0, 0, 1, 1, 1],
                    [1, 0, 0, 0, 0, 0],
                    [0, 0, 1, 1, 1, 0],
                    [0, 0, 0, 0, 0, 0],
                    [0, 1, 1, 1, 1, 0],
                    [0, 0, 0, 0, 0, 0]]) == [2, 3, 3, 4], "3rd example"
