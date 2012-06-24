// 11228 uva

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
typedef pair<double, PII> PDPII;
typedef vector<PII> VPII;

class FindUnionSet {
public:
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

void unitTestsFUS()
{
	FindUnionSet fus(10);
	assert(fus.numberOfDisjoints() == 10);
	assert(fus.getParent(1) == 1);
	assert(fus.isSameSet(1,9) == false);
	fus.join(1,9);
	assert(fus.numberOfDisjoints() == 9);
	assert(fus.isSameSet(1,9) == true);
}

vector<PDPII> edgeList;
vector<double> MST;
int graphSize;

void kruskalsMST()  {
	FindUnionSet fus(graphSize);
	MST.clear();

	while(fus.numberOfDisjoints() > 1 && !edgeList.empty()) {
		PDPII curEdge = edgeList.front();

		if(!fus.isSameSet(curEdge.second.first, curEdge.second.second)) {
			fus.join(curEdge.second.first, curEdge.second.second);
			MST.push_back(curEdge.first);
		}
		pop_heap(edgeList.begin(), edgeList.end(), greater<PDPII>());
		edgeList.pop_back();
	}
}

double dist(PII u, PII v) {
	return sqrt((u.first-v.first)*(u.first-v.first) +
				(u.second-v.second)*(u.second-v.second));
}

void buildGraph(VPII &nodeList) {
	edgeList.clear();
	REP(i, nodeList.size())
		FOR(j, i+1, nodeList.size())
		edgeList.push_back(mp(dist(nodeList[i], nodeList[j]), mp(i,j)));
	make_heap(edgeList.begin(), edgeList.end(), greater<PDPII>());
}

int main(int argc, char *argv[])
{
	int nTests; scanf("%d", &nTests);
	FOR(test, 1, nTests+1) {
		int r;
		scanf(" %d %d", &graphSize, &r);
		VPII nodeList;
		int x, y;
		REP(i, graphSize) {
			scanf(" %d %d", &x, &y);
			nodeList.push_back(mp(x,y));
		}
		buildGraph(nodeList);
		kruskalsMST();
		int numOfStates = 0;
		double totalRoads = 0.0;
		double totalRails = 0.0;
		REP(i, MST.size()) {
			if(MST[i] > r) {
				totalRails += MST[i];
				++numOfStates;
			}
			else totalRoads += MST[i];
		}
		printf("Case #%d: %d %d %d\n", test, numOfStates+1, 
			   int(round(totalRoads)), int(round(totalRails)));
	}

	return 0;
}
