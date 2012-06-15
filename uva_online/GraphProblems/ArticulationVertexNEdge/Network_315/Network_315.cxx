#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

VI dfsNum, dfsLow, dfsParent, articulationVertex;
VVI G;
int dfsNumIndex;
int dfsRoot, dfsRootChildren;

void dfsArticulationVertCount(int curVertex)
{
	dfsNum[curVertex] = dfsLow[curVertex] = dfsNumIndex++;

	for(int i = 0; i < G[curVertex].size(); i++) {
		if(dfsNum[G[curVertex][i]] == 0) {
			dfsParent[G[curVertex][i]] = curVertex;
			if(curVertex == dfsRoot) dfsRootChildren++;
			dfsArticulationVertCount(G[curVertex][i]);
			if(dfsLow[G[curVertex][i]] >= dfsNum[curVertex])
				articulationVertex[curVertex] = 1;
			dfsLow[curVertex] = min(dfsLow[curVertex],
									dfsLow[G[curVertex][i]]);
		}
		else if(dfsParent[G[curVertex][i]] != curVertex)
			dfsLow[curVertex] = min(dfsLow[curVertex], 
									dfsNum[G[curVertex][i]]);
	}

}


int main(int argc, char *argv[])
{
	int N, curVertex;
	char input[500];
	while(scanf(" %d", &N), N != 0) {
		G = VVI(N);
		while(true)
		{
			scanf(" %[^\n]s", input);
			char *tok = strtok(input, " ");
			curVertex = atoi(tok);
			if(curVertex == 0) break;
			while( (tok = strtok(NULL, " ")) ) {
				int connectedNode = atoi(tok);
				G[connectedNode-1].push_back(curVertex-1);
				G[curVertex-1].push_back(connectedNode-1);
			}
		}

/*		for(int i = 0; i < G.size(); i++) {
			for(int j = 0; j < G[i].size(); j++) 
				printf("%d ", G[i][j]);
			printf("\n");
			}*/

		dfsNum = VI(N, 0);
		dfsLow = VI(N, 0);
		dfsParent = VI(N, 0);
		dfsNumIndex = 1;
		articulationVertex = VI(N, 0);
		dfsRoot = 0;
		dfsRootChildren = 0;
		dfsArticulationVertCount(0);
		articulationVertex[dfsRoot] = (dfsRootChildren > 1) ? 1: 0;
		printf("%d\n", accumulate(articulationVertex.begin(),
								  articulationVertex.end(), 0));
	}

	return 0;
}
