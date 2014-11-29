// The solution for K = (pi+...+pj), while V = (pi+...+qj)!*(di^pi)*...*(dj^pj)
// Using segment tree to keep this information.
// Use lazy propagation to update only when required.
// Also for K>MOD V=0

#include <cstdio>
#include <cstring>

#define REP(i,n) for(int i = 0; i < (n); ++i)
#define FOR(i,st,nd) for(int i = (st); 
typedef long long LL;

#define MOD 1000003
inline LL MODMUL(LL x, LL y){
	return (x*y)%MOD;
}

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
		exponent = exponent >> 1;
		base = MODMUL(base, base);
	}
	return res;
}


struct STNode {
	STNode(){}
	STNode(int l, int m, int h, STNode *_l, STNode *_r)
		: low(l), mid(m), high(h), left(_l), right(_r), upd(0) {
		K = left->K+right->K;
		V = MODMUL(left->V, right->V);
		d = MODMUL(left->d, right->d);
	}
	STNode(int l, int m, int h, LL _d, LL _p)
		: low(l), mid(m), high(h), d(_d), K(_p), upd(0), left(0), right(0) {
		V = modularPow(d,K);
	}
	void update(LL _upd){
		K += _upd*(high+1-low);
		if(low == high) 
			upd = 0, V = modularPow(d, K);
		else
			upd += _upd, V = MODMUL(V, modularPow(d, _upd));
	}

	void update() {
		if(left && right) {
			K = left->K+right->K;
			V = MODMUL(left->V, right->V);
		}
	}

	void propagate() {
		if(left && right && upd) {
			left->update(upd);
			right->update(upd);
			upd = 0;
		}
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
	void query(int low, int high, LL &K, LL &V) {
		K = 0, V = 1;
		query(root, low, high, K, V);
		//fprintf(stderr, " %lld %lld %lld %lld\n", K, MODMUL(V, fact(K)), fact(K), V);
		
		V = MODMUL(V, fact(K));
		if(K > MOD) V = 0;
	}

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
		if(cur->low == low && cur->high == high)
			cur->update(upd);
		else {
			cur->propagate();
			if(cur->mid < low) 
				update(cur->right, low, high, upd);
			else if(cur->mid >= high)
				update(cur->left, low, high, upd);
			else {
				update(cur->left, low, cur->mid, upd);
				update(cur->right, cur->mid+1, high, upd);
			}
			cur->update();
		}
	}

	void query(STNode *cur, int low, int high, LL &K, LL &V) {
		if(cur->low == low && cur->high == high) {
			K += cur->K, V = MODMUL(V, cur->V);
			//fprintf(stderr, "%d %d %lld %lld\n", low, high, cur->K, cur->V);
		}
		else {
			cur->propagate();
			if(cur->mid < low)
				query(cur->right, low, high, K, V);
			else if(cur->mid >= high)
				query(cur->left, low, high, K, V);
			else {
				query(cur->left, low, cur->mid, K, V);
				query(cur->right, cur->mid + 1, high, K, V);
			}
			cur->update();
		}
	}
private:
	STNode *root;
	STNode *leaves;
	int size;
};

int main(int argc, char *argv[]) {
	memset(factorial, -1, sizeof factorial);
	factorial[0] = factorial[1] = 1;
	int N, Q, a, d, p, low, high, v, q;
	LL K, V;
	scanf(" %d", &N);
	//fprintf(stderr, "%d\n", N);
	STNode *treeLeaves = new STNode[N];
	REP(i, N) scanf(" %d %d %d", &a, &d, &p), 
		treeLeaves[i] = STNode(i,i,i,d,p); //fprintf(stderr, "%d %d %d\n", a, d, p);

	scanf(" %d", &Q);
	//fprintf(stderr, "%d\n", Q);
	SegmentTree tree(treeLeaves, N);
	REP(i, Q) {
		scanf(" %d", &q);
		if(q == 1) { // update 
			scanf(" %d %d %d", &low, &high, &v);
			//fprintf(stderr, "%d %d %d %d\n", q, low, high, v);
			tree.update(low-1, high-1, v);
		}
		else { // query
			scanf(" %d %d", &low, &high);
			//fprintf(stderr, "%d %d %d\n", q, low, high);
			tree.query(low-1, high-1, K, V);
			printf("%lld %lld\n", K, V);
		}
	}

	return 0;
}
