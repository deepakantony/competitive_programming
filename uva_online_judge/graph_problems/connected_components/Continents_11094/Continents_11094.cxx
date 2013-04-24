#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>

#define REP(i,n) for(int i = 0; i < (n); i++)


using namespace std;

typedef pair<int, int> PII;

int M, N;
char map[20][20];

void printMap() {
	REP(row, M) {
		REP(col, N) printf("%d", map[col][row]);
		printf("\n");
	}
}

int floodFill(int x, int y, char label)
{
	char startLabel = map[x][y];
	queue< PII > Q;
	Q.push(make_pair(x,y));
	int count = 0;
	map[x][y] = label;
	count++;
	while(!Q.empty()) {

		PII curNode = Q.front();
		x = curNode.first; y = curNode.second;
		Q.pop();

		if(y == 0) {
			if(map[x][N-1] == startLabel) {
				count++; map[x][N-1] = label;
				Q.push(make_pair(x, N-1));
			}
		}
		else if(map[x][y-1] == startLabel) {
			count++; map[x][y-1] = label;
			Q.push(make_pair(x, y-1));
		}

		if(y == (N-1)) {
			if(map[x][0] == startLabel) {
				count++; map[x][0] = label;
				Q.push(make_pair(x, 0));
			}
		}
		else if(map[x][y+1] == startLabel) {
			count++; map[x][y+1] = label;
			Q.push(make_pair(x, y+1));
		}

		if(x != 0 && map[x-1][y] == startLabel) {
			count++; map[x-1][y] = label;
			Q.push(make_pair(x-1, y));
		}
		if(x != (M-1) && map[x+1][y] == startLabel) {
			count++; map[x+1][y] = label;
			Q.push(make_pair(x+1, y));
		}
	}
	return count;
}

int main(int argc, char *argv[])
{
	int x, y;
	while(scanf(" %d %d", &M, &N) != EOF) {
		memset(map, -1, sizeof map);
		REP(row, M) 
			scanf(" %s", map[row]);

		scanf(" %d %d", &x, &y);

		char startLabel = map[x][y];
		// flood fill kings land first
		floodFill(x, y, '?');

		int continent = 0;
		REP(row, M) REP(col, N) {
			if(map[row][col] == startLabel)
				continent = max(continent, floodFill(row, col, '?'));
		}
		printf("%d\n", continent);
	}

	return 0;
}
