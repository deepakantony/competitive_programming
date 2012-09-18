#include <cstdio>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <cassert>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
typedef pair<int, int> PII;
typedef pair<int, PII> PIPII;

#define PH pop_heap 
#define MH make_heap 
#define GT greater<PIPII>() 
#define mp make_pair

char grid[700][700];
int M, N;
vector<PIPII> Q;

// returns the number of grid points it can attack. If it can be attacked by
// pre installed gun then return -1.
int getCountOfGridsThisPointCanAttack(int row, int col) {
	int count = 0;
	if(row-2 >= 0) {
		if(col-2 >= 0 && grid[row-1][col-1] != 'P') {
			if(grid[row-2][col-2] == 'G') return -1;
			if(grid[row-2][col-2] == 'F') count++;
		}
		if(col+2 < N && grid[row-1][col+1] != 'P') {
			if(grid[row-2][col+2] == 'G') return -1;
			if(grid[row-2][col+2] == 'F') count++;
		}
	}
	if(row+2 < M) {
		if(col-2 >= 0 && grid[row+1][col-1] != 'P') {
			if(grid[row+2][col-2] == 'G') return -1;
			if(grid[row+2][col-2] == 'F') count++;
		}
		if(col+2 < N && grid[row+1][col+1] != 'P') {
			if(grid[row+2][col+2] == 'G') return -1;
			if(grid[row+2][col+2] == 'F') count++;
		}
	}
	return count;
}
	

// This function generate the priority queue for the given input. 
void preProcess() {
	Q.clear();
	REP(row, M) REP(col, N)
		if(grid[row][col] == 'F') {
			int count = getCountOfGridsThisPointCanAttack(row, col);
			if(count >= 0) // if -1 it cannot contain a gun
				Q.push_back(mp(count, mp(row,col)));
		}
	MH(Q.begin(), Q.end(), GT);
}

// This function will place a gun at the given (row, col) location and also
// mark any attaching point as unusable by gun
void updateSurroundings(int row, int col) {
	grid[row][col] = 'F';
	if(row-2 >= 0) {
		if(col-2 >= 0 && grid[row-1][col-1] != 'P') {
			assert(grid[row-2][col-2] != 'G');
			grid[row-2][col-2] = 'N';
		}
		if(col+2 < N && grid[row-1][col+1] != 'P') {
			assert(grid[row-2][col+2] != 'G');
			grid[row-2][col+2] = 'N';
		}
	}
	if(row+2 < M) {
		if(col-2 >= 0 && grid[row+1][col-1] != 'P') {
			assert(grid[row+2][col-2] != 'G');
			grid[row+2][col-2] = 'N';
		}
		if(col+2 < N && grid[row+1][col+1] != 'P') {
			assert(grid[row+2][col+2] != 'G');
			grid[row+2][col+2] = 'N';
		}
	}
}

// counts the total possible placements for guns
int totalPossible() {
	int count = 0;

	while(!Q.empty()) {
		int row = Q.front().second.first;
		int col = Q.front().second.second;
		if(grid[row][col] == 'F') 
			count++, updateSurroundings(row, col);
		PH(Q.begin(), Q.end(), GT); Q.pop_back();
	}

	return count;
}


int main(int argc, char *argv[])
{
	while(scanf("%d %d", &M, &N) != EOF && M != 0) {
		REP(i, M) scanf("%s", grid[i]);
		preProcess();
		printf("%d\n", totalPossible());
	}
	return 0;
}

