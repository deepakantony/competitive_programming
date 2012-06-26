import math

def findQuadrandInfo(x, y, quadrantInfo):
    if x >= 0:
        if y >= 0:
            quadrantInfo[0] = 1 
        else: quadrantInfo[3] = 1
    else:
        if y >= 0:
            quadrantInfo[1] = 1
        else: quadrantInfo[2] = 1

def add(q1, q2, sum):
    sum[0] = q1[0] + q2[0]
    sum[1] = q1[1] + q2[1]
    sum[2] = q1[2] + q2[2] 
    sum[3] = q1[3] + q2[3]

def addTo(q1, sum):
    sum[0] += q1[0]
    sum[1] += q1[1]
    sum[2] += q1[2]
    sum[3] += q1[3]

def reflectQX(q):
    q[0], q[3] = q[3], q[0]
    q[1], q[2] = q[2], q[1]

def reflectQY(q):
    q[0], q[1] = q[1], q[0]
    q[3], q[2] = q[2], q[3]

def printQuadrant(q):
    print "%d %d %d %d" % (q[0], q[1], q[2], q[3])

def left(index):
    return 2*index + 1

def right(index):
    return 2*index + 2

def parent(index):
    return (index-4)/2


class Tree:
    def __init__(self, _nPoints):
        self.curI = self.curJ = 0
        self.curReflect = ''
        self.nPoints = _nPoints
        self.size = int(math.ceil(math.log(self.nPoints))*self.nPoints)
        self.tree = [ [0]*4 for x in xrange(self.size) ]
        self.q = [0]*4
        self.initialize(0, 0, self.nPoints-1)


    def initialize(self, cur, low, high):
	if low == high :
            (x,y) = raw_input().split()
            findQuadrandInfo(int(x), int(y), self.tree[cur])
	else:
            l = left(cur)
            r = right(cur)
            mid = (low+high)/2
            self.initialize(l, low, mid)
            self.initialize(r, mid+1, high)
            add(self.tree[l], self.tree[r], self.tree[cur])

    def getInfo(self, cur, low, high):
	if low == high:
            addTo(self.tree[cur], self.q)
	elif low >= self.curI and high <= self.curJ:
            addTo(self.tree[cur], self.q)
	else:
            l = left(cur)
            r = right(cur)
            mid = (low+high)/2
            if self.curI > mid: self.getInfo(r, mid+1, high)
            elif self.curJ <= mid: self.getInfo(l, low, mid)
            else:
                self.getInfo(r, mid+1, high)
                self.getInfo(l, low, mid)


    def reflectQ(self, quadrant):
	if self.curReflect: reflectQX(quadrant)
	else: reflectQY(quadrant)

    def swapReflect(self, cur, low, high):
	if low == high:
            self.reflectQ(self.tree[cur])
	else:
            mid = (low+high)/2
            self.swapReflect(left(cur), low, mid)
            self.swapReflect(right(cur), mid+1, high)
            self.reflectQ(self.tree[cur])


    def reflect(self, cur, low, high):
	if low == high: self.reflectQ(self.tree[cur])
	elif low >= self.curI and high <= self.curJ:
            self.swapReflect(cur, low, high)
	else:
            l = left(cur)
            r = right(cur)
            mid = (low+high)/2
            if self.curI > mid: self.reflect(r, mid+1, high)
            elif self.curJ <= mid: self.reflect(l, low, mid)
            else:
                self.reflect(l, low, mid)
                self.reflect(r, mid+1, high)

            add(self.tree[l], self.tree[r], self.tree[cur])

    def printTree(self):
        for entry in self.tree:
            print entry

    def doQueries(self, nQueries):
        for query in xrange(nQueries):
            (self.curReflect, self.curI, self.curJ) = raw_input().split()
            self.curI = int(self.curI) - 1
            self.curJ = int(self.curJ) - 1
            if self.curReflect == 'C':
                self.q = [0, 0, 0, 0]
                self.getInfo(0, 0, self.nPoints-1)
                printQuadrant(self.q)
            else:
                self.reflect(0, 0, self.nPoints-1)

def solveQuadrantQueries():
    nPoints = int(raw_input())
    tree = Tree(nPoints)
    nQueries = int(raw_input())
    tree.doQueries(nQueries)

def main():
    solveQuadrantQueries();

if __name__ == "__main__":
    main()
