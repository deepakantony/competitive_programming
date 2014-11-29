#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define mod 1000000007
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

typedef long long int LL;

// handles the negative numbers
inline LL modme(LL num) { return num < 0 ? mod + num : num%mod; }

char inputBoard[200][200];
LL origBoard[400][400];
LL sumBoard[400][400];
LL memo[400][400];
LL startIndex[400];
LL endIndex[400];
int N, S, M, newN; // newN will be 2*N-1
int Lx, Ly;

template<typename T>
void printBoard(T &board, int size) {
	REP(i, size) {
		REP(j, size) cout << board[i][j] << "\t";
		printf("\n");
	}
}

// From the original input, this function creates a diamond shaped board, which 
// is double the size.
void initResultBoard() {
	newN = 2*N-1;
	memset(origBoard, 0, sizeof origBoard);
	memset(memo, 0, sizeof memo);
	memset(sumBoard, 0, sizeof sumBoard);
    
    // index in diamond
    int coldmndi = N-1, coldmndj = N;
    int stepcoli = -1, stepcolj = 1;
    int starti = 0, startj = 0;
    int incri = 1, incrj = 0;
    int row = 0, col = 0;
	REP(x, newN) {
		startIndex[x] = coldmndi;
		endIndex[x] = coldmndj;
		for(int y = coldmndi; y < coldmndj; y+=2) {

            if(inputBoard[row][col] == '.')
                origBoard[x][y] = 1;
			else if(inputBoard[row][col] == 'L') 
                origBoard[x][y] = 1, Lx = x, Ly = y;
			memo[x][y] = origBoard[x][y];

            row = row-1, col = col+1;
		}
        if (coldmndi <= 0) {
            swap(stepcoli, stepcolj);
			starti = N-1, startj = 0;
            incri = 0, incrj = 1;
		}
        coldmndi += stepcoli;
        coldmndj += stepcolj;
        starti += incri, startj += incrj;
        row = starti, col = startj;
	}
}
    
// Calculates the partial sum
void constructSumBoard() {
	int startj;
	REP(i, newN) {
		startj = i >= N ? 0 : startIndex[i];

		for(int j = startj; j < newN; ++j) {
			sumBoard[i][j] = memo[i][j];
            if(j > 0) sumBoard[i][j] += sumBoard[i][j-1];
            if(i > 0) sumBoard[i][j] += sumBoard[i-1][j];
			if(j > 0 && i > 0) 
				sumBoard[i][j] -= sumBoard[i-1][j-1];
			sumBoard[i][j] = modme(sumBoard[i][j]);
		}

	}
}

// Recalculate the board values based on the partial sums
void recalculateResultBoard() {
	int x_s_1, y_s_1, xs, ys;
	LL sub;
	REP(x, newN) {
        for(int y = startIndex[x]; y < endIndex[x]; y+=2) 
            if(origBoard[x][y] == 1) {
				xs = min(newN-1,x+S);
				ys = min(newN-1, y+S);
				x_s_1 = x-S-1, y_s_1 = y-S-1;
				sub = 0;
                memo[x][y] = sumBoard[xs][ys];
                if(x_s_1 >= 0 && y_s_1 >= 0)
                    memo[x][y] += sumBoard[x_s_1][y_s_1];
                if(x_s_1 >= 0) 
                    sub += sumBoard[x_s_1][ys];
                if(y_s_1 >= 0)
                    sub += sumBoard[xs][y_s_1];
				memo[x][y] = modme(memo[x][y]-sub);
			}
	}
}

// This is DP solution. The idea is to calculate the number of ways to move from
// the every location at each step. For step 1 it would be the total number of
// positions that can be reached from that location given S. For step 2 it would
// be the sum of these values at every location and so on.
// To do this easily for M steps, at every step we need to calculate the partial
// sum just like we do for the classic maxsum DP problem. Using these values, we
// can calculate the total number of ways at each step in O(N^2) ways. This gives
// us the total complexity at O(MN^2).
// Note that to do this partial sums easily, the board must be rotated to a 
// diamond shape so that our calculation is easy.
LL fairyChess() {
	initResultBoard();
	M--;
	REP(step, M) {
        constructSumBoard();
        recalculateResultBoard();
	}
	constructSumBoard();
	int x = Lx, y = Ly;
	int xs = min(newN-1,x+S);
	int ys = min(newN-1, y+S);
	int x_s_1 = x-S-1, y_s_1 = y-S-1;
	memo[x][y] = sumBoard[xs][ys];
	if(x_s_1 >= 0 && y_s_1 >= 0)
		memo[x][y] = (memo[x][y] + sumBoard[x_s_1][y_s_1])%mod;
	if(x_s_1 >= 0) 
		memo[x][y] = modme(memo[x][y] - sumBoard[x_s_1][ys]);
	if(y_s_1 >= 0)
		memo[x][y] = modme(memo[x][y] - sumBoard[xs][y_s_1]);

	
	return memo[Lx][Ly];
}
    
int main(int argc, char *argv[]) {
    int T; scanf(" %d", &T);
	while(T--) {
		scanf(" %d %d %d", &N, &M, &S);
		REP(i, N) 
			scanf(" %s", inputBoard[i]);

        printf("%lld\n", fairyChess());
	}
	return 0;
}

