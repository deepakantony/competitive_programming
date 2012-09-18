#include <cstdio>
#include <cstring>
#include <ctime>

#define FOR(i, st, n) for(int (i) = (st), _n = (n); (i) < _n; ++(i))

typedef unsigned long long LL;

int matrix[11][2];
LL memo[11][11];
int pos[11][11];


// memo(l, r) = 0 if (l+1 == r)
//            = min(memo(l, l+i) + memo(l+i, r) + 
//               row(l) * row(l+i) * col(r-1) 
//               for all i -> [l+1, r))
LL optimalMult(int left, int right) 
{
	if(right > left && memo[left][right] == -1ll) {
		if(right == (left+1)) {
			memo[left][right] = 0;
			pos[left][right] = 0;
		}
		else {
			FOR(position, left+1, right) {
				LL curVal = 
					optimalMult(left, position) + 
					optimalMult(position, right) +
					matrix[left][0] * matrix[position][0] * matrix[right-1][1];
				if(curVal < memo[left][right]) {
					memo[left][right] = curVal;
					pos[left][right] = position;
				}
			}
		}
	}
	return memo[left][right];
}

// backtrack printing
void printMultiplySeq(int left, int right)
{
	if(right == (left+1))
		printf("A%d", right);
	else {
		printf("(");
		printMultiplySeq(left, pos[left][right]);
		printf(" x ");
		printMultiplySeq(pos[left][right], right);
		printf(")");
	}
}

void printPos(int nMatrices) {
	FOR(row, 0, nMatrices) {
		FOR(col, 0, nMatrices) 
			printf ("%d ", pos[row][col]);
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	clock_t begin = clock();
	int nMatrices;
	int nCase = 1;
	scanf( " %d", &nMatrices);
	while( nMatrices > 0) {
		FOR(m, 0, nMatrices) 
			scanf(" %d %d", &matrix[m][0], &matrix[m][1]);

		memset(memo, -1, sizeof memo);
		optimalMult(0, nMatrices);
		printf("Case %d: ", nCase++);
		printMultiplySeq(0, nMatrices);
		//printPos(nMatrices);
		printf("\n");
		scanf( " %d", &nMatrices);
	}
	fprintf(stderr, "Time taken: %.4f seconds\n", 
			(float)(clock()-begin)/CLOCKS_PER_SEC);
	return 0;
}
