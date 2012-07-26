// The solution for K = (pi+...+pj), while V = (pi+...+qj)!*(di^pi)*...*(dj^pj)
// Using segment tree to keep this information.
// Use lazy propagation to update only when required.

#include <cstdio>

#define REP(i,n) for(int i = 0; i < (n); ++i)
#define FOR(i,st,nd) for(int i = (st); 
typedef long long LL;

#define MOD 1000003
#define MODMUL(x,y) ((((x)%MOD)*((y)%MOD))%MOD)

LL factorial[MOD+10];
LL fact(LL num) {
	if(num >= MOD) return MODMUL(MODMUL((num/MOD), fact(num%MOD)), fact(MOD-1));
	if(factorial[num] != -1) return factorial[num];
	return factorial[num] = MODMUL(num, fact(num-1));
}


struct STNode {
	STNode(int l, int m, int h, STNode *_l, STNode *_r)
		: low(l), mid(m), high(h), left(_l), right(_r) {}
	int low, mid, high;
	LL K, V;
	int update;
	STNode *left, *right;
};

class SegmentTree {
public:
	SegmentTree() {}

private:
	STNode *root;
};

int main(int argc, char *argv[]) {
	return 0;
}
