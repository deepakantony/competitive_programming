// 10048 uva

// At first I was thinking of separating based on strongly connected 
// components. But this can be easily solved just by find MST and separating
// small and large edge lengths. The number of large edges (>r) will give the
// number of states :)

#include <vector>
#include <cstdio>
#include <cstring>
#include <utility>
#include <cassert>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); i++)
#define FOR(i, st, n) for(int i = (st); i < (n); i++)
#define mp make_pair

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef pair<int, PII> PIPII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

class FindUnionSet {
public:
	FindUnionSet() : parent(), size(0) {}
	FindUnionSet(int size) : parent(size), size(size) { 
		REP(i, size) parent[i] = i;
	}
	int numberOfDisjoints() {return size;}
	void join(int u, int v) { 
		if(isSameSet(u,v))
			return;
		parent[getParent(u)] = parent[v]; 
		--size;
	}
	int getParent(int u) { 
		return (parent[u] == u ? u : parent[u] = getParent(parent[u])); 
	}
	bool isSameSet(int u, int v) { return getParent(u) == getParent(v); }

private:
	VI parent;
	int size;
};

vector<PIPII> edgeList;
vector<PIPII> MST;
int graphSize;
FindUnionSet fus;

void kruskalsMST()  {
	fus = FindUnionSet(graphSize);
	MST.clear();

	while(fus.numberOfDisjoints() > 1 && !edgeList.empty()) {
		PIPII curEdge = edgeList.front();

		if(!fus.isSameSet(curEdge.second.first, curEdge.second.second)) {
			fus.join(curEdge.second.first, curEdge.second.second);
			MST.push_back(curEdge);
		}
		pop_heap(edgeList.begin(), edgeList.end(), greater<PIPII>());
		edgeList.pop_back();
	}
}

VVI MSTPath;
VI dfsVisited;
VVPII mstGraph;

void buildMSTGraph() {
	mstGraph = VVPII(graphSize);
	REP(i, MST.size()) {
		int u = MST[i].second.first;
		int v = MST[i].second.second;
		int w = MST[i].first;
		mstGraph[u].push_back(mp(v,w));
		mstGraph[v].push_back(mp(u,w));
	}
}


int dfs(int curNode, int reachNode) {
	//printf("%d ", curNode);
	if(dfsVisited[curNode] > 0) return 0;
	dfsVisited[curNode] = 1;
	int maxDist = 0;
	REP(i, mstGraph[curNode].size()) {
		int v = mstGraph[curNode][i].first;
		int w = mstGraph[curNode][i].second;
		if(v == reachNode) {
			//printf("%d %d %d\n", curNode, v, w);
			maxDist = w; break;
		}
		if(dfsVisited[v] < 0) {
			int val = dfs(v, reachNode);
			if(val>0) {//printf(":%d  ", val);
				maxDist = max(maxDist, max(val, w));
			}
		}
	}		
	return maxDist;
}
	

int initMstPath() {
	MSTPath = VVI(graphSize);
	REP(i, MSTPath.size()) MSTPath[i] = VI(graphSize, -1);
	buildMSTGraph();
}


int main(int argc, char *argv[])
{
	int S, Q;
	for(int test = 1; scanf(" %d %d %d", &graphSize, &S, &Q) != EOF &&
			(S != 0 || Q != 0 || graphSize != 0); ++test) {
		int x, y, w;
		edgeList.clear();
		REP(i, S) {
			scanf(" %d %d %d", &x, &y, &w);
			edgeList.push_back(mp(w, mp(x-1,y-1)));
		}
		make_heap(edgeList.begin(), edgeList.end(), greater<PIPII>());
		kruskalsMST();
		initMstPath();
		if(test != 1) printf("\n");
		printf("Case #%d\n", test);
		
		REP(i, Q) {
			scanf(" %d %d", &x, &y);
			--x; --y;
			if(fus.isSameSet(x, y)) {
				if(MSTPath[x][y] == -1)  {
					dfsVisited = VI(graphSize, -1);
					MSTPath[x][y] = MSTPath[y][x] = dfs(x,y);
				}
				printf("%d\n", MSTPath[x][y]);
			}
			else printf("no path\n");
		}
	}

	return 0;
}


