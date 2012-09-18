#include <stack>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <utility>
#include <string>
#include <cassert>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> II;
typedef vector<II> VII;
typedef vector<VII> VVII;
typedef vector<string> VS;
typedef queue<II> QII;

#define mp make_pair
#define REP(i, n) for(int i = 0; i < (n); i++)

int setBit(int n, int bitIndex) {
	return ((1 << (bitIndex-1)) | n);
}

int unsetBit(int n, int bitIndex) {
	return (~(1 << (bitIndex-1))) & n;
}

bool isBitSet(int n, int bitIndex) {
	return ((1 << (bitIndex-1)) & n) != 0;
}

int flipBit(int n, int bitIndex) {
	return isBitSet(n, bitIndex) ? 
		unsetBit(n, bitIndex) : setBit(n, bitIndex);
}

void bitFuncsUnitTest() {
	assert(unsetBit(2, 2) == 0);
	assert(unsetBit(8, 16) == 8);
	assert(setBit(0, 4) == 8);
	assert(setBit(16, 5) == 16);
	assert(isBitSet(32, 6) == true);
	assert(isBitSet(16, 6) == false);
	assert(isBitSet(7, 1) == true);
}

void backtrackPrint(const VVII &backtrack,
					const vector<VS> &btText,
					int curVertex,
					int curLight,
					stack<string> &output)
{
	II next = backtrack[curVertex][curLight];
	for(int nextVertex = next.first, nextLight = next.second;
		curVertex != nextVertex || curLight != nextLight ; 
		next = backtrack[nextVertex][nextLight],
			nextVertex = next.first, nextLight = next.second) {
		//fprintf(stderr, "Stack %d %d\n", nextVertex, nextLight);
		output.push(btText[curVertex][curLight]);
		curVertex = nextVertex;
		curLight = nextLight;
	}
}

void bfs(const VVI &G, const VVI &lightG) {
	int source = 0; 
	int destVert = G.size()-1;
	int destLight = (1<<destVert);

	VVII backtrack(G.size(), VII( (1<<G.size())));
	REP(i, backtrack.size()) REP(j, backtrack[i].size())
		backtrack[i][j] = mp(-1,-1);
	vector<VS> btText(G.size(), VS((1<<G.size())));

	QII Q;
	char text[100];
	backtrack[source][1] = mp(0,1);
	Q.push(mp(0,1));
	while(!Q.empty()) {
		II curState = Q.front();
		int curVert = curState.first;
		int curLight = curState.second;
		Q.pop();

		//fprintf(stderr, "%d %d\n", curVert, curLight);

		if(curVert == destVert && curLight == destLight) {
			stack<string> output;
			backtrackPrint(backtrack, btText, curVert, curLight, output);
			printf("The problem can be solved in %d steps:\n", 
				   (int)output.size());
			while(!output.empty()) {
				string op = output.top();
				output.pop();
				printf("- %s\n", op.c_str());
			}
			return;
		}

		// first, get into any nodes that are accessible
		REP(i, G[curVert].size()) {
			int nextVert = G[curVert][i];
			//fprintf(stderr, "Cur light: %d Next Vertex: %d\n", curLight, nextVert);
			if(isBitSet(curLight, nextVert+1) && 
			   backtrack[nextVert][curLight].first == -1) {
				//fprintf(stderr, " - Cur light: %d Next Vertex: %d\n", curLight, nextVert);

				Q.push(mp(nextVert, curLight));
				backtrack[nextVert][curLight] = mp(curVert, curLight);

				sprintf(text, "Move to room %d.", nextVert+1);
				btText[nextVert][curLight] = string(text);
			}
		}

		// Second, flip any lights accessible
		REP(i, lightG[curVert].size()) {
			int nextVert = lightG[curVert][i]+1;
			int nextLight;
			if(isBitSet(curLight, nextVert)) {
				nextLight = unsetBit(curLight, nextVert);
				sprintf(text, "Switch off light in room %d.", nextVert);
			}
			else {
				nextLight = setBit(curLight, nextVert);
				sprintf(text, "Switch on light in room %d.", nextVert);
			}
			//fprintf(stderr, "Next light: %d Cur Vertex: %d\n", nextLight, curVert);
			//fprintf(stderr, "Backtrack: %d %d\n",
			// backtrack[curVert][nextLight].first, 
			//   backtrack[curVert][nextLight].second);
			if(isBitSet(nextLight, curVert+1) && 
			   backtrack[curVert][nextLight].first == -1) {
				//fprintf(stderr, " - Next light: %d Cur Vertex: %d\n", nextLight, curVert);
				Q.push(mp(curVert, nextLight));
				backtrack[curVert][nextLight] = mp(curVert, curLight);
				btText[curVert][nextLight] = string(text);
			}
		}
	}
	printf("The problem cannot be solved.\n");
}

int main(int argc, char *argv[])
{
	bitFuncsUnitTest();
	int numOfRooms, numOfDoors, numOfLights;
	int villa = 1;
	while(scanf(" %d %d %d", &numOfRooms, &numOfDoors, &numOfLights) != EOF &&
		  (numOfRooms != 0 || numOfDoors != 0 || numOfLights != 0))
	{
		//if(villa != 1) 

		int u, v;
		VVI G(numOfRooms);
		REP(index, numOfDoors) {
			scanf(" %d %d", &u, &v); 
			--u; --v;
			G[u].push_back(v); G[v].push_back(u);
		}
		VVI lightG(numOfRooms);
		REP(i, numOfLights) {
			scanf(" %d %d", &u, &v); 
			--u; --v;
			lightG[u].push_back(v);
		}

		printf("Villa #%d\n", villa++);
		bfs(G, lightG);
		printf("\n");
	}

	return 0;
}
