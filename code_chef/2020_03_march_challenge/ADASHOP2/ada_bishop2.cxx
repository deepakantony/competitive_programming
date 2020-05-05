/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
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
#include <string>
#include <map>
#include <iterator>

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

typedef vector<VVPII> VVVPII;

void dfs(const VVVPII &G, VVI &v, int &vcount, VPII &out, int r, int c) {
	if(vcount == 32) return;
	if(v[r][c]) return;
	v[r][c] = 1;
	vcount += 1;
	//cout << r << " " <<  c << " : " << G[r][c].size() << endl;
	for(auto rc : G[r][c]) {
		int nr = rc.first, nc = rc.second;
		if(!v[nr][nc]) {
			out.push_back(mp(nr, nc));
			dfs(G, v, vcount, out, nr, nc);
			if(vcount == 32) break;
			out.push_back(mp(r,c));
		}
	}
}

void solve() {
	VVVPII G(8, VVPII(8, VPII()));
	for(int r = 0; r < 8; r+=1)
		for(int c = (r%2==0)?0:1; c < 8; c+=2)
			for(int dr = -1; dr <= 1; dr+=2)
				for(int dc = -1; dc <= 1; dc+=2) {
					int nr = r+dr, nc = c+dc;
					if( nr >= 0 && nr < 8 && nc >= 0 && nc < 8 )
						G[r][c].push_back(mp(nr,nc));
				}
	int T; cin >> T;
	while(T--) {
		int r, c; cin >> r >> c; --r; --c;
		VVI v(8, VI(8, 0));
		int vcount = 0;
		VPII out;
		dfs(G, v, vcount, out, r, c);
		assert(vcount==32);
		assert(out.size() <= 63);
#if 0
		REP(r, 8) {
			REP(c, 8) {
				cout << v[r][c] << " ";
			}
			cout << endl;
		}
#endif
		REP(r, 8) REP(c, 8) {
			if((r+c+2)%2 == 0)
				assert(v[r][c]!= 0);
		}
		cout << out.size() << endl;
		for(auto o : out)
			cout << o.first+1 << " " << o.second+1 << endl;
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
