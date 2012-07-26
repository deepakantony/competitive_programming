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

LL modularPow(LL base, LL exponent) {
	LL res = 1;
	while(exponent > 0) {
		if(exponent % 2 == 1) res = MODMUL(res, base);
		exponent >>= 1;
		base = MODMUL(base, base);
	}
	return res;
}


struct STNode {
	STNode(int l, int m, int h, STNode *_l, STNode *_r)
		: low(l), mid(m), high(h), left(_l), right(_r), upd(0) {
		K = left->K+right->K;
		V = MODMUL(left->V, right->V);
	}
	STNode(int l, int m, int h, LL _d, LL _p)
		: low(l), mid(m), high(h), d(_d), K(_p), upd(0), left(0), right(0) {
		V = MODMUL(d,K);
	}
	void update(LL _upd){
		K += _upd;
		upd = 0;
		V = MODMUL(d,K);
	}

	int low, mid, high;
	LL K, V, upd, d;
	STNode *left, *right;
};

class SegmentTree {
public:
	SegmentTree(STNode *_leaves, int _size) 
		: leaves(_leaves), size(_size) { root = build(0, size-1); }

	void update(int low, int high, LL upd) {
		update(root, low, high, upd);
	}
	void query(int low, int high, LL &K, LL &V) {}

private:
	STNode *build(int low, int high) {
		STNode *cur;
		if(low == high) cur = &leaves[low];
		else {
			int mid = (low+high)/2;
			cur = new STNode(low, mid, high, 
							 build(low, mid), 
							 build(mid+1, high)); 
		}
		return cur;
	}

	void update(STNode *cur, int low, int high, LL upd) {
		if(cur->low == low && cur->high == high && low == high) 
			cur->update(upd);
		else if(cur->low == low && cur->high == high) 
			cur->upd += upd;
		else {
			
		}
	}
	

private:
	STNode *root;
	STNode *leaves;
	int size;
};

int main(int argc, char *argv[]) {
	return 0;
}
