import heapq


Graph = []
N = 0
# This dijkstras keeps track of another array visitedCount[i], which gives
# number of shortest paths from 0 to i.
def dijkstras():
    Q = []
    visitedCount = [0]*N
    dist = [float("inf")]*N
    heapq.heappush(Q, tuple([0, 0]) )
    dist[0] = 0
    visitedCount[0] = 1
    while len(Q) > 0:
        curDist, curNode = heapq.heappop(Q)
        for (nextNode, weight) in Graph[curNode]:
            nextDist = curDist + weight
            if nextDist == dist[nextNode]:
                visitedCount[nextNode] += visitedCount[curNode]
            elif nextDist < dist[nextNode]:
                visitedCount[nextNode] = visitedCount[curNode]
                dist[nextNode] = nextDist
                heapq.heappush(Q, (nextDist, nextNode))

    return visitedCount[N-1]

def main():
    global N
    global Graph
    T = int(raw_input())
    for test in xrange(T):
        N, M = tuple( map(int, raw_input().split()) )
        Graph = []
        for x in xrange(N): Graph.append([])
        for edge in xrange(M):
            Ai, Bi, Ci = tuple( map(int, raw_input().split()) )
            Graph[Ai-1].append((Bi-1, Ci))
            Graph[Bi-1].append((Ai-1, Ci))

        print dijkstras()

if __name__ == "__main__":
    main()


# Tomya is a girl. She loves Chef Ciel very much.
# Today, too, Tomya is going to Ciel's restaurant. Of course, Tomya would like 
# to go to Ciel's restaurant as soon as possible. Therefore Tomya uses one of 
# the shortest paths from Tomya's house to Ciel's restaurant. On the other hand, 
# Tomya is boring now to use the same path many times. So Tomya wants to know the 
# number of shortest paths from Tomya's house to Ciel's restaurant. Your task is 
# to calculate the number under the following assumptions.
# This town has N intersections and M two way roads. The i-th road connects from 
# the Ai-th intersection to the Bi-th intersection, and its length is Ci. Tomya's 
# house is in the 1st intersection, and Ciel's restaurant is in the N-th 
# intersection.
# Input
# 
# The first line contains an integer T, the number of test cases. Then T test 
# cases follow. The first line of each test case contains 2 integers N, M. Then 
# next M lines contains 3 integers denoting Ai, Bi and Ci.
# Output
# 
# For each test case, print the number of shortest paths from Tomya's house to 
# Ciel's restaurant.
# Constraints
# 
# 1 <= T <= 10
# 2 <= N <= 10
# 1 <= M <= N * (N - 1) / 2
# 1 <= Ai, Bi <= N
# 1 <= Ci <= 10
# Ai != Bi
# If i != j and Ai = Aj, then Bi != Bj
# There is at least one path from Tomya's house to Ciel's restaurant.
# Sample Input
# 
# 2
# 3 3
# 1 2 3
# 2 3 6
# 1 3 7
# 3 3
# 1 2 3
# 2 3 6
# 1 3 9
# Sample Output
# 
# 1
# 2
# Explanations
# 
# In the first sample, only one shortest path exists, which is 1-3.
# In the second sample, both paths 1-2-3 and 1-3 are the shortest paths.
