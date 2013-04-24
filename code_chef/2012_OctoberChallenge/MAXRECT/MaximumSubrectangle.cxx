/*
  Problem: Maximum Sub-rectangle
  Link: http://www.codechef.com/OCT12/problems/MAXRECT
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: I don't have the optimal solution; i'm just approximating it to the
  single subrectangle with maximum sum. No time for kadane's algorithm; so 
  copied it from web http://alexeigor.wikidot.com/kadane. Anyways, this will
  only give a partial answer - gave me 0.3 points :)
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

void solveMaxSubrectangle() {
    int W, H;
 
	while(scanf("%d%d", &H, &W) != EOF){
    LL t = 0;
    int a[300][300];
    LL pr[300];
    LL S = -1000000009, s = 0;
	int k, l, x1 = 0,x2 = 0,y1 = 0,y2 = 0,j;

 
    for( int i = 0; i < H; i++)
        for( j = 0; j < W; j++)
            scanf("%d", &a[i][j]);
 
    for( int z = 0; z < H; z++)
    {
        for(int i = 0; i < W; i++) pr[i] = 0;
 
        for(int x = z; x < H; x++)
        {
            t = 0;
            s = -1000000009;
            j = 0;
            k = 0; l = 0;
            for(int i = 0; i < W; i++)
            {
                pr[i] = pr[i] + a[x][i];
                t = t + pr[i];
                if( t > s)
                {
                    s = t;
                    k = i;
                    l = j;
                }
                if( t < 0 )
                {
                    t = 0;
                    j = i + 1;
                }
            }
            if( s > S)
            {
                S = s;
                x1 = z;
                y1 = l;
                x2 = x;
                y2 = k;
            }
        }
    }
	//if(x1 > x2 ) swap(x1, x2); if(y1 > y2) swap(y1,y2);
	printf("%d %d\n", x2-x1+1, y2-y1+1);
	FOR(i, x1, x2+1) 
		if(i == x2) printf("%d\n", i);
		else printf("%d ", i);
	FOR(j, y1, y2+1)
		if(j == y2) printf("%d\n", j);
		else printf("%d ", j);
	}
}

void solveMaxSubrectangleSilly() {
    int W, H;
    int t = 0;
    int a[300][300];
    int pr[300];
    int S = -1, s = 0, k, l, x1 = 0,x2 = 0,y1 = 0,y2 = 0,j;
 
	scanf("%d%d", &H, &W);
 
	int maxn = -1000000009, maxrow, maxcol;
    for( int i = 0; i < H; i++)
        for( j = 0; j < W; j++) {
            scanf("%d", &a[i][j]);
			if(a[i][j] > maxn) {
				maxn = a[i][j];
				maxrow = i; maxcol = j;
			}
		}
	printf("1 1\n%d\n%d\n", maxrow, maxcol);
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveMaxSubrectangle();
	//solveMaxSubrectangleSilly();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
