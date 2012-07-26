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
		: low(l), mid(m), high(h), left(_l), right(_r), update(0) {
		K = left->K+right->K;
		V = MODMUL(left->V, right->V);
	}
	STNode(int l, int m, int h, int k, int v)
		: low(l), mid(m), high(h), K(k), V(v), update(0), left(0), right(0) {
	}

	int low, mid, high;
	LL K, V;
	int update;
	STNode *left, *right;
};

class SegmentTree {
public:
	SegmentTree(STNode *_leaves, int _size) 
		: leaves(_leaves), size(_size) { root = build(0, size-1); }

	void update(int low, int high, LL upd) {}
	void query(int low, int high, LL &K, LL &V) {}

private:
	STNode *build(int low, int high) {
		STNode *cur;
		if(low == high) cur = &leaves[low];
		else {
			int mid = (low+high)/2;
			cur = new Node(low, mid, high, 0, 0);
			cur->left = build(low, mid);
			cur->right = build(mid+1, high);
		}
		return cur;
	}

private:
	STNode *root;
	STNode *leaves;
	int size;
};

int main(int argc, char *argv[]) {
	return 0;
}
