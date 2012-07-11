#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

typedef vector<int> VI;
typedef unsigned int uint;
typedef vector<uint> VU;

#define GSIZE 38
#define s 0
#define t 37
#define INF 1000000000
int res[GSIZE][GSIZE];
int parent[GSIZE];

uint augment(int curVertex, int minimumEdgeWeight) {
	if(curVertex != s && parent[curVertex] != -1) {
		int v = parent[curVertex];

		minimumEdgeWeight = augment(v, min(minimumEdgeWeight, res[v][curVertex]));
		res[v][curVertex] -= minimumEdgeWeight;
		res[curVertex][v] += minimumEdgeWeight;
	}
	return minimumEdgeWeight;
}

int getFlow() {
	int mf = 0;
	int f;
	do {
		memset(parent, -1, sizeof parent);
		int curVertex = s;
		
		VU dist(GSIZE, INF);
		dist[curVertex] = 0;
		queue<int> Q; Q.push(curVertex);
		while(!Q.empty() && Q.front() != t) {
			curVertex = Q.front(); Q.pop();
			REP(i, GSIZE) if(res[curVertex][i] > 0 && dist[i] == INF)
				Q.push(i), parent[i] = curVertex, dist[i] = dist[curVertex]+1;

		}

		
		f = augment(t, INF);
		if(f!=INF) mf += f;
	
	} while(f!=INF);

	return mf;
}

void printOutput() {

	REP(i, 10) {
		int user = i + 27;
		int app = 0;
		FOR(node, 1, 27) if(res[user][node] == 1)
		{ app = node; break; }
		if(app) printf("%c", (char)app + 'A' - 1);
		else printf("_");
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	// inputs
	int totalUsers = 0;
	char curApp, nUsers, curComp;
	char line[100];
	memset(res, 0, sizeof res);
	bool found = false;
	while(true) {

		
		fgets(line, 100, stdin);

		//printf("%s", line);
		if(isalpha(line[0]) && feof(stdin) == 0) {
			found = true;
			curApp = line[0] - 'A' + 1; // node for applications start at 1
			nUsers = line[1] - '0';
			res[s][curApp] = nUsers;
			totalUsers += nUsers;

			for(int i = 3; line[i] != ';'; ++i) {
				curComp = line[i] - '0' + 27; // node for computers start at 27

				res[curApp][curComp] = 1;
			}
		}
		else if(found){
			found = false;
			FOR(i, 27, t) res[i][t] = 1;

			if(getFlow() != totalUsers)
				printf("!\n");
			else
				printOutput();

			memset(res, 0, sizeof res);
			totalUsers = 0;
		}
		if(feof(stdin) != 0) break;
	} 
	return 0;
}
