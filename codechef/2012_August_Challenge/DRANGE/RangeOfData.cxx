// Problem Range Of Data

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long LL;

struct SNode {
	LL min, max;
	LL update;
};

// This is segment tree; figure out the rest!
class STree {
public:
	STree(int _size) : size(_size) {
		tree = new SNode[2*(int)pow(2, floor(log(double(size))/log(2.0)+1))];
		build(0, 1, size);
	}

	void update(int low, int high, int value) {
		update(0, 1, size, low, high, value);
	}

	LL getThatFinalValue() {
		fprintf(stderr,"Min - %lld Max - %lld\n", tree[0].min, tree[0].max);
		return tree[0].max-tree[0].min;
	}

	~STree() { delete tree; }
private:
	void build(int curIndex, int low, int high) {
		tree[curIndex].update = 0;
		if(low == high) tree[curIndex].min = tree[curIndex].max = low;
		else {
			tree[curIndex].min = low, tree[curIndex].max = high;
			int mid = (low+high)/2;
			build(left(curIndex), low, mid);
			build(right(curIndex), mid+1, high);
		}
	}
	void update(int curIndex, int cl, int ch, int low, int high, int value) {
		if(cl == ch)
			tree[curIndex].max = tree[curIndex].min = 
				tree[curIndex].min + value; 
		else if(cl==low && ch==high) {
			tree[curIndex].update += value;
			updateMe(curIndex);
		}
		else {
			propagate(curIndex);
			int cm = (cl+ch)/2; // current mid
			if(high <= cm) 
				update(left(curIndex), cl, cm, low, high, value);
			else if(low > cm)
				update(right(curIndex), cm+1, ch, low, high, value);
			else {
				update(left(curIndex), cl, cm, low, cm, value);
				update(right(curIndex), cm+1, ch, cm+1, high, value);
			}
			update(curIndex);
		}
	}

	void updateMe(int curIndex) {
		tree[curIndex].min += tree[curIndex].update;
		tree[curIndex].max += tree[curIndex].update;			
	}

	void propagate(int curIndex) {
		if(tree[curIndex].update != 0) {
			tree[left(curIndex)].update += tree[curIndex].update;
			updateMe(left(curIndex));
			tree[right(curIndex)].update += tree[curIndex].update;
			updateMe(right(curIndex));
			tree[curIndex].update = 0;
		}
	}
	void update(int curIndex) {
		tree[curIndex].min = min(tree[left(curIndex)].min, 
								 tree[right(curIndex)].min);
		tree[curIndex].max = max(tree[left(curIndex)].max, 
								 tree[right(curIndex)].max);
	}
	inline int left(int curIndex) { return 2*(curIndex+1)-1; }
	inline int right(int curIndex) { return 2*(curIndex+1); }
	SNode *tree;
	int size;
};

int main(int argc, char *argv[]) 
{
	int T; scanf("%d", &T);
	int M, N, w, x, y, z;
	while(T--) {
		scanf("%d %d", &N, &M);
		STree st(N);
		while(M--) {
			scanf("%d %d %d %d", &w, &x, &y, &z);
			st.update(x, y, w==2?-z:z);
		}
		printf("%lld\n", st.getThatFinalValue());
	}
	return 0;
}
