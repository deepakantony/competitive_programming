#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cassert>
#include <queue>
#include <functional>
#include <map>
#include <set>

using namespace std;

#define REP(i, st, n) for(int (i) = (st), _n = (n) ; (i) < (_n); ++(i))
#define FOREACH(it, ctnr) for(__typeof__(ctnr.begin()) it = ctnr.begin(); \
							  it != ctnr.end(); ++it)
#define INF 1000000000

bool isBitOn(int num, int pos) { return (num&(1<<pos)) != 0; }
int unsetBit(int num, int pos) { return (num&(~(1<<pos))); }

int finalCost[13][13];
int memo[13][(1<<13)];
int nDVD; 
int stores[13];
int costSaving[13];


#define ii pair<int, int>
#define VI vector<int>
#define VII vector< ii >
#define VVII vector< VII >
#define VMII vector< map<int, int > >
class Graph {
public:
	Graph(int size) : adjList(size) {} 
	int addEdge(int vertex1, int vertex2, int weight) {
		if(adjList.size() <= vertex1 || adjList.size() <= vertex2)
			adjList.resize(max(vertex1+1, vertex2+1));
		if(adjList[vertex1].find(vertex2) == adjList[vertex1].end())
			adjList[vertex1][vertex2] = weight;
		else
			adjList[vertex1][vertex2] = min(adjList[vertex1][vertex2],weight);
		if(adjList[vertex2].find(vertex1) == adjList[vertex2].end())
			adjList[vertex2][vertex1] = weight;
		else
			adjList[vertex2][vertex1] = min(adjList[vertex2][vertex1],weight);
		
	}
	int size() {return adjList.size(); }
	void shortestPath(int vertex, VI &dist) {
		assert(dist.size() == adjList.size());
		assert(vertex >= 0 && vertex < adjList.size());

		fill(dist.begin(), dist.end(), INF);
		set< ii > minSet;
		minSet.insert(ii(0, vertex));
		while(!minSet.empty()) {
			int curVertex = minSet.begin()->second;
			int curDist = minSet.begin()->first;
			dist[curVertex] = min(dist[curVertex], curDist);
			minSet.erase(minSet.begin());
			FOREACH(it, adjList[curVertex]) 
				if(dist[it->first] > (it->second+dist[curVertex]))
					minSet.insert(ii(it->second+dist[curVertex], it->first));
		}
	}
private:
	VMII adjList;
};



void updateDistForTSP(Graph &G) 
{
	REP(i, 0, nDVD+1) {
		VI finalTravelDist(G.size());
		G.shortestPath(stores[i], finalTravelDist);
		REP(j, 0, nDVD+1) {
			finalCost[i][j] = finalTravelDist[stores[j]];
			//printf("%d ", finalCost[i][j]);
		}
		//printf("\n");
	}
}

int TSP(int curpos, int bitmask) {
	if(memo[curpos][bitmask] == -INF) {
		if(bitmask == 0) 
			memo[curpos][bitmask] = -finalCost[curpos][0];
		else {
			REP(pos, 1, nDVD+1) {
				if(isBitOn(bitmask, pos)) {
					int res = costSaving[pos] - finalCost[curpos][pos] +
						TSP(pos, unsetBit(bitmask, pos));
					res = max(res, TSP(curpos, unsetBit(bitmask, pos)));
					memo[curpos][bitmask] = res;
				}
			}
		}
	}
	return memo[curpos][bitmask];
}

int TSP() {
	return TSP(0, unsetBit((1<<(nDVD+1))-1, 0));
}

int main(int argc, char *argv[])
{
	int nTests; scanf("%d", &nTests);
	while(nTests--) {
		int N, M; scanf(" %d %d", &N, &M);
		Graph G(N+1);
		while(M--) {
			int v1,v2, w1,w2;
			scanf(" %d %d %d.%d", &v1, &v2, &w1, &w2);
			G.addEdge(v1,v2,w1*100+w2);
		}
		int sum = 0;
		scanf(" %d", &nDVD);
		stores[0] = 0;
		costSaving[0] = 0;
		REP(i, 1, nDVD+1) {
			int cost1, cost2;
			scanf(" %d %d.%d", &stores[i], &cost1, &cost2);
			costSaving[i] = cost1*100 + cost2;
		}
		updateDistForTSP(G);
		REP(i, 0, nDVD+1) REP(j, 0, 1<<(nDVD+1)) memo[i][j] = -INF;
		int tspRes = TSP();
		int res = tspRes;
		//printf("--%d %d %d\n", sum, tspRes, res);
		if(res <= 0) printf("Don't leave the house\n");
		else printf("Daniel can save $%d.%02d\n", res/100, res%100);
	}
	return 0;
}

