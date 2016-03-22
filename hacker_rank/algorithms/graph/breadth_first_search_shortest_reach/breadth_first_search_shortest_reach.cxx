/*
  Problem: breadth first search: shortest reach
  Link: https://www.hackerrank.com/challenges/bfsshortreach
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: bfs
*/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>
#include <iomanip>
#include <queue>

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
#define EPS (1e-9)
#define FLT_EQ(x,y) ((fabs((x)-(y))) < EPS)

void solve()
{
	int T; cin >> T;
	while( T-- )
	{
		int N, M; cin >> N >> M; // nodes & edge count
		VVI G(N);
		while(M--) {
			int x,y; cin >> x >> y; x--;y--; // start x & y from 0
		
			G[x].push_back(y);
			G[y].push_back(x);
		}
		int S; cin >> S; S--; // start S from 0
		
		VI dist(N, -1);
		queue<int> Q;
		Q.push(S);
		dist[S] = 0;
		int cur_dist = 0;
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
		
			for( auto y : G[x] )
				if ( dist[y] == -1 ) {
					Q.push(y);
					dist[y] = cur_dist + 6;
				}
		
			cur_dist += 6;
		}
		
		REP(i, N)
		{
			if( i == S ) continue;
			cout << dist[i] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
