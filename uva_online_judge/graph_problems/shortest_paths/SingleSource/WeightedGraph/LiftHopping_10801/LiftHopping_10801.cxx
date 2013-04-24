#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

#define INF 1000000000
#define REP(i, n) for(int i = 0; i < (n); i++)
#define mp make_pair
#define OSOP ostream_iterator<int>(cerr, " ")

typedef pair<int,int> II;
typedef pair<int, II> III;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<II> VII;
typedef vector<VII> VVII;
typedef priority_queue<III, vector<III>, greater<III> > PQIII;
typedef stack<int> SI;
typedef vector<SI> VSI;

int dijkstras(const VI &time, const VVI &floors, int destination, int maxf)
{
	// prepare the input to be in a workable format
	// A exist[][] is created that maps the floors[] 
	VVI exist(floors.size(), VI(maxf+1, -1));
	REP(i, floors.size()) {
		REP(j,floors[i].size()) {
			exist[i][floors[i][j]] = j;
		}
	}

	VVI distance(floors.size(), VI(maxf+1, INF));

	int curNode, curElevator, curDist;
	PQIII Q;
	REP(i, floors.size())
		if(exist[i][0] >= 0) {
			Q.push(mp(0,mp(i, 0)));
			distance[i][0] = 0;
		}

	int res = INF;
	while(!Q.empty()) {
		curDist = Q.top().first;
		curElevator = Q.top().second.first;
		curNode = Q.top().second.second;
		//fprintf(stderr,"%d = %d %d\n", curDist, curElevator, curNode);
		Q.pop();
		if(curNode == destination) { res = curDist; break; }
		if(curDist == distance[curElevator][curNode]) {
			int nextDist, nextElevator, nextNode;

			// 2 things I can do here - I can change the elevator or I can 
			// stay in the same elevator and move to a different floor

			// First lets check if I can change elevators
			nextNode = curNode;
			REP(elev, floors.size()) 
				if(elev != curElevator && exist[elev][nextNode] >= 0) {
					nextDist = curDist + 60;
					if(distance[elev][nextNode] > nextDist) {
						distance[elev][nextNode] = nextDist;
						Q.push(mp(nextDist, mp(elev, nextNode)));
					}
				}

			// Now check if there is any floors accessible by staying in the same
			// elevator
			nextElevator = curElevator;
			for(int i = -1; i < 2; i +=2) { // 2 if statements
				int nextIndex = exist[nextElevator][curNode]+i;
				if(nextIndex >=0 && nextIndex < floors[nextElevator].size()) {
					nextNode = floors[nextElevator][nextIndex];
					nextDist = curDist + time[nextElevator] * 
						abs(nextNode-curNode);
					if(distance[nextElevator][nextNode] > nextDist) {
						distance[nextElevator][nextNode] = nextDist;
						Q.push(mp(nextDist, mp(nextElevator, nextNode)));
					}
				}
			}
		}
	}
	return res;
}

int main(int argc, char *argv[])
{
	clock_t start = clock();
	int numOfElevators;
	while(scanf(" %d", &numOfElevators) != EOF) {
		int finalFloor;
		scanf(" %d", &finalFloor);

		VI time;
		int t;
		REP(i, numOfElevators) scanf(" %d", &t), time.push_back(t);
		scanf("\n");
		VVI floors;
		char input[1000];
		int f; int maxf = 0;
		REP(i, numOfElevators) {
			gets(input);
			VI elevatorFloors;
			char *tokenized = strtok(input, " ");
			while(tokenized != NULL && 
				  sscanf(tokenized, " %d", &f) != EOF) {
				elevatorFloors.push_back(f);
				maxf = max(maxf, f);
				tokenized = strtok(NULL, " ");
			}
			floors.push_back(elevatorFloors);
		}

		int res;
		if((res = dijkstras(time, floors, finalFloor, maxf)) == INF)
			printf("IMPOSSIBLE\n");
		else printf("%d\n", res);
			
	}
	fprintf(stderr, "Time taken: %.5fs.\n", ((float)clock()-(float)start)/CLOCKS_PER_SEC);

	return 0;
}
