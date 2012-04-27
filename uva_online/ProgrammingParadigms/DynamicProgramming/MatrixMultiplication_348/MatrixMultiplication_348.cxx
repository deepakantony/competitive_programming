#include <cstdio>
#include <cstring>

#define FOR(i, st, n) for(int (i) = (st), _n = (n); (i) < _n; ++(i))

typedef unsigned long long LL;

LL matrix[101][2];
LL memo[101][101];
LL row[101][101];
LL col[101][101];
LL pos[101][101];

int optimalMult(int left, int right) 
{
	if(right > left && memo[left][right] == -1ll) {
		if(right == (left+1)) {
			memo[left][right] = 0;
			row[left][right] = matrix[left][0];
			col[left][right] = matrix[left][1];
			pos[left][right] = 0;
		}
		else {
			
		}
	}
	return memo[left][right];
}


