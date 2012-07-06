#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

#define INF 1000000000
#define REP(i, n) for(int i = 0; i < (n); i++)
#define mp make_pair

typedef pair<int,int> II;
typedef pait<int, II> III;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<II> VII;
typedef vector<VII> VVII;
typedef priority_queue<III> PQIII;
typedef stack<int> SI;
typedef vector<SI> VSI;

int dijkstras(const VI &time, const VSI &floors, int destination, int maxf)
{
	int curNode = 0;
	int curElevator = 0;
	int curDist = 0;

	VI dist(maxf+1, INF);
	PQII Q;
	REP(i, floors.size()) {
		if(!floors[i].empty() && floors[i].
	Q.push(mp(0,mp());
	dist[0] = 0;

	while(!Q.empty()) {
		curDist = Q.top().first;
		curElevator = Q.top().second.first;
		curNode = Q.top().second.second;
		Q.pop();
		if(curDist == dist[curNode]) {
			REP(i, floors.size()) {
				if(!floors[i].empty() && floors[i].top() == curNode) {
					floors[i].pop();
					int nextDist = curDist 
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int numOfElevators;
	while(scanf(" %d", &numOfElevators) != EOF) {
		int finalFloor;
		scanf(" %d", &finalFloor);

		VI time;
		int t;
		REP(i, numOfElevators) scanf(" %d", &t), time.push_back(t);

		VVI floors(numOfElevators);
		char input[1000];
		int f; int maxf = 0;
		REP(i, numOfElevators) {
			gets(input);
			SI elevatorFloors;
			while(sscanf( input, " %d", &f) != EOF) {
				elevatorFloors.push(f);
				maxf = max(maxf, f);
			}
			floors.push_back(elevatorFloors);
		}

		int res;
		if((res = dijkstras(time, floors, finalFloor, maxf)) == INF)
			printf("IMPOSSIBLE\n");
		else printf("%d\n", res);
			
	}

	return 0;
}
