#include <queue>
#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef pair<int,PII> PIPII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef priority_queue<PII> PQPII;
typedef priority_queue<int> PQI;
typedef priority_queue<PIPII> PQPIPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, n) for(int i = (st); i < (n); ++i)
#define mp make_pair


void dijkstraSSSP(const VVPII &G,  // adj list
				  const int source,
				  VI &distance,
				  VI &path)
{
	distance = VI(G.size(), -1);
	path = VI(G.size(), -1);
	
	PQPII
}
