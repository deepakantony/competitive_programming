#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

float graph[20][20][20];
int backtrack[20][20][20];
int graphSize;

void fw() {
	FOR(step, 1, graphSize) 
		REP(k, graphSize) REP(i, graphSize) REP(j, graphSize) {
		float newval = graph[i][k][step-1]*graph[k][j][0];
		if(graph[i][j][step] < newval) {
			graph[i][j][step] = newval;
			backtrack[i][j][step] = k;
		}
	}
}

int bt(int i, int j, int step, vector<int> &path) {
	if(step == 0) {
		path.push_back(i); 
		path.push_back(j);
	}
	else {
		int k = backtrack[i][j][step];
		if(k != -1) {
			bt(i, k, step-1, path);
			path.pop_back();
			bt(k, j, 0, path);
		}
	}
	return path.size();
}

void bt() {
/*	FOR(step, 1, graphSize) { printf("Step: %d\n", step);
		REP(i, graphSize) {REP(j, graphSize) 
			{ printf("%f\t", graph[i][j][step]); }
			printf("\n");
		}
	}
	FOR(step, 1, graphSize) { printf("Step: %d\n", step);
		REP(k, graphSize) REP(i, graphSize) {REP(j, graphSize) 
			{ printf("%d\t", backtrack[i][j][step]); }
			printf("\n");
		}
		}*/
	vector<int> minPath;
	FOR(step, 1, graphSize) { 
		if(!minPath.empty()) break;
		REP(i, graphSize) {
		if(graph[i][i][step] > 1.01f) {
			bt(i, i, step, minPath);
			break;
		}
		}
	}

	if(minPath.empty()) printf("no arbitrage sequence exists\n");
	else {
		REP(i, minPath.size()) {
			printf("%d", minPath[i]+1);
			if(i != minPath.size()-1) printf(" ");
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	while(scanf(" %d", &graphSize) != EOF) {
		memset(graph, 0, sizeof graph);
		REP(i, graphSize) REP(j, graphSize) {
			if( i == j) graph[i][j][0] = 1.f;
			else scanf(" %f", &graph[i][j][0]);
			backtrack[i][j][0] = -1;
		}

		fw();
		bt();
	}
	return 0;
}
