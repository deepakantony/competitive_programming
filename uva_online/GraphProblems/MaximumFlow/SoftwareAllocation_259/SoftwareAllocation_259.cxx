#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

typedef vector<int> VI;
typedef unsigned int uint;

#define GSIZE 38
#define s 0
#define t 37
#define INF -1
uint res[GSIZE][GSIZE];
int parent[GSIZE];

int augment(int curVertex, int &minimumEdgeWeight) {
	if(curVertex == s) return minimumEdgeWeight;
	else {
		int v = parent[curVertex];
		minimumEdgeWeight = augment(v, min(minimumEdgeWeight, res[v][curVertex]));
		res[v][curVertex] -= minimumEdgeWeight;
		res[curVertex][v] += minimumEdgeWeight;
	}
}

int getFlow() {
	int mf = 0;

	return mf;
}

void printOutput() {

}

int main(int argc, char *argv[]) {
	// inputs
	int totalUsers = 0;
	char curApp, nUsers, curComp;
	char line[100];
	memset(res, INF, sizeof res);

	while(fgets(line, 100, stdin) != NULL) {
		if(isalpha(line[0])) {
			curApp = line[0] - 'A' + 1; // node for applications start at 1
			nUsers = line[1] - '0';
			res[s][curApp] = nUsers;
			totalUsers += nUsers;

			for(int i = 3; line[i] != ';'; ++i) {
				curComp = line[i] - '0' + 27; // node for computers start at 27
				res[curApp][curComp] = 1;
			}
		}
		else {
			FOR(i, 27, t) res[i][t] = 1;

			if(getFlow() != totalUsers)
				printf("!\n");
			else
				printOutput();

			//printf("%d \n", totalUsers);

			memset(res, INF, sizeof res);
			totalUsers = 0;
		}
	}
	return 0;
}
