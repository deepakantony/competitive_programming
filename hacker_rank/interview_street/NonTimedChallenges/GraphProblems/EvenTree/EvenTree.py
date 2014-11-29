import sys
graphSize = 0
adjMatrix = []
visited = []
edgeList = []

# Function tells me how many vertices can be reached from the given vertex.
# This count includes the vertex itself. 
# Note that this is a dfs on the graph.
def dfs(curVert):
    visited[curVert] = 1
    count = 1
    for nextVertex in xrange(graphSize):
        if adjMatrix[curVert][nextVertex] == 1 and visited[nextVertex] != 1:
            count += dfs(nextVertex)

    return count

# Identifies the number of edges that can be removed without breaking the even
# vertex forest.
# Removes each edge and finds out if it can be removed by counting from both
# ends of the edge.
def maxNumberOfEdges():
    res = 0
    global visited

    for edge in edgeList:
        u, v = edge
        adjMatrix[u][v] = adjMatrix[v][u] = 0
        visited = [-1] * graphSize
        countU = dfs(u)

        if countU % 2 != 0:
            adjMatrix[u][v] = adjMatrix[v][u] = 1
        else:
            res += 1
    return res

def main():
    N, M = tuple([int(x) for x in raw_input().split()])
    global graphSize 
    graphSize = N
    global adjMatrix
    singleRow = [0]*graphSize
    for row in xrange(graphSize):
        adjMatrix.append(list(singleRow))
    global edgeList
    
    for e in xrange(M):
        u, v = tuple([int(x) for x in raw_input().split()])
        u -= 1
        v -= 1
        edgeList.append(tuple((u,v)))

        adjMatrix[u][v] = adjMatrix[v][u] = 1

    print maxNumberOfEdges()
            
    
if __name__ == "__main__":
    main()
