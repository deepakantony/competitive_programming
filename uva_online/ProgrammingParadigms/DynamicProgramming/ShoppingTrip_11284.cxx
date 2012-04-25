#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cassert>
#include <queue>
#include <greater>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))
#define FOREACH(it, ctnr) for(__typeof__(ctnr.begin()) it = ctnr.begin(); \
							  it != ctnr.end(); ++it)

bool isBitOn(int num, int pos) { return (num&(1<<pos)) != 0; }
int unsetBit(int num, int pos) { return (num&(~(1<<pos))); }

int dist[13][13];
int memo[13][(1<<13)-1];
int nDVD;

int TSP(int curpos, int bitmask) {
	if(memo[curpos][bitmask] == -1) {
		if(bitmask == 0) memo[curpos][bitmask] = dist[curpos][0];
		else {
			REP(pos, 1, nDVD) {
				if(isBitOn(bitmask, pos)) {
					int res = TSP(pos, unsetBit(bitmask, pos));
					if(memo[curpos][bitmask] == -1 ||
					   res < memo[curpos][bitmask])
						memo[curpos][bitmask];
				}
			}
		}
	}
	return memo[curpos][bitmask];
}

int TSP() {
	return TSP(0, unsetBit((1<<nDVD)-1, 0));
}

#define VI vector<int> 
#define VVI vector< VI >
class Graph {
	Graph(int size) : adjList(size) {} 
	int addEdge(int vertex1, int vertex2, int weight) {
		if(adjList.size() <= vertex1 || adjList.size() <= vertex2)
			adjList.resize(max(vertex1+1, vertex2+1));
		adjList[vertex1].push_back(make_pair(vertex2, weight));
		adjList[vertex2].push_back(make_pair(vertex1, weight));
	}
	int numberOfVertices() {adjList.size(); }
	void shortestPath(int vertex, vector<int> &dist) {
		assert(dist.size() == adjList.size());
		assert(vertex >= 0 && vertex < adjList.size());

		fill(dist.begin(), dist.end(), MAX_INT);
		priority_queue<int, greater<int> > Q;
		FOREACH(it, adjList[vertex])
			Q.push(*it);
		dist[vertex] = 0;
		while(!Q.empty()) {
			int curVertex = Q.top();
			Q.pop();
			dist[curVertex] = 
		}
	}
private:
	VVI adjList;
};

int main(int argc, char *argv[])
{

	return 0;
}

