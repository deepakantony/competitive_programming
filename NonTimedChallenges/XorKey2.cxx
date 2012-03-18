#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef unsigned short ushort;

bool isNthBitOn(ushort n, int pos) { return ((n & (1 << pos)) != 0); }

struct BNode {
	BNode(BNode *l, BNode *r, BNode *p, ushort x) 
		: left(l), right(r), parent(p), data(x) {}
	BNode *left, *right, *parent;
	ushort data;
};
struct BTree {
	BTree() { root = new BNode(0,0,0,0); cheatSet.clear(); }
	void insert(ushort x) {
		if(cheatSet.find(x) != cheatSet.end()) {
			insertBin(root, x, 15);
			cheatSet.insert(x);
		}
	}
	void insertBin(BNode *cur, ushort x, int bitPos) {
		if(bitPos == 0) {
			if(isNthBitOn(x,bitPos))
				cur->left = new BNode(0, 0, cur, x);
			else
				cur->right = new BNode(0, 0, cur, x);
		}
		else {

		}
	}
	void insert2(ushort x) {
		if(!root) root = new BNode(0, 0, 0, x);
		else {
			BNode *l = findLastOf(root, x);
			if(l) {
				if(l->data > x) l->left = new BNode(0, 0, l, x);
				else l->right = new BNode(0, 0, l, x);
			}
		}
	}
	BNode* findLastOf(BNode *cur, ushort x) {
		if(!cur || cur->data == x) return 0;
		if(!cur->left && !cur->right) return cur;
		if(cur->data > x)
			if(!cur->left) return cur; else return findLastOf(cur->left, x);
		if(cur->data < x)
			if(!cur->right) return cur; else return findLastOf(cur->right, x);
	}

	void flatten() {
		flattened.clear();
		for(auto key: cheatSet)
			flattened.push_back(key);
		cheatSet.clear();
		sort(flattened.begin(), flattened.end());
	}
	void flatten2() {
		flattened.clear();
		flatten(root);
	}
	void flatten(BNode *cur) {
		if(!cur) return;
		flatten(cur->left);
		flattened.push_back(cur->data);
		flatten(cur->right);
	}

	ushort getMaxXor(ushort key) {
		if(hashCache.find(key) != hashCache.end())
			return hashCache[key];
		int low = 0, high = flattened.size()-1;
		for(int bitPos = 15; low < high && bitPos >= 0; --bitPos)
			if(isNthBitOn(key, bitPos))
				high = getHignWithOffBit(low, high, bitPos);
			else
				low = getLowWithOnBit(low, high, bitPos);
		if(high == low && low >= 0 && low < flattened.size()) {
			hashCache[key] = flattened[low] ^ key;
			return flattened[low] ^ key;
		}
		hashCache[key] = 0;
		return 0;
	}
	
	int getHignWithOffBit(int low, int high, int bitPos) {
		int ch = high;
		while(low <= high) {
			int mid = (low+high)/2;
			if(!isNthBitOn(flattened[mid], bitPos)) {
				ch = mid;
				low = mid+1;
			} else high = mid-1;
		}
		return ch;
	}

	int getLowWithOnBit(int low, int high, int bitPos) {
		int cl = low;
		while(low <= high) {
			int mid = (low+high)/2;
			if(isNthBitOn(flattened[mid], bitPos)) {
				cl = mid;
				high = mid-1;
			} else low = mid + 1;
		}
		return cl;
	}

	ushort getMaxXorNaive(ushort key) { 
		ushort max = 0; 
		getMaxXor(root, key, max);
		return max;
	}
	void getMaxXor(BNode *cur, ushort key, ushort &max) {
		if(!cur) return;
		ushort temp = cur->data ^ key;
		if(temp > max) max = temp;
		getMaxXor(cur->left, key, max); getMaxXor(cur->right, key, max);
	}
	void print() { print(root); }
	void print(BNode *cur) { 
		if(!cur) return;
		print(cur->left);
		printf("%hu, ", cur->data);
		print(cur->right);
	}
	BNode *root;
	vector<ushort> flattened;
	unordered_set<ushort> cheatSet;
	unordered_map<ushort, ushort> hashCache;
};

struct SNode {
	BTree *setOfKeys;
	SNode *left, *right;
	int low, high;

	SNode(SNode *l, SNode *r, int _low, int _high, ushort *keyList) 
		:left(l), right(r), low(_low), high(_high) {
		setOfKeys = new BTree;
		for(int index = low; index <= high; ++index)
			setOfKeys->insert(keyList[index]);
		setOfKeys->flatten();
	}
	ushort getMaxXor(ushort key) {
		return setOfKeys->getMaxXor(key);
	}
	void print() {
		printf("[%d %d]\n(", low, high);
		setOfKeys->print();
		printf(")\n");
	}
};

struct STree {
	ushort *keyList; int nKeys; SNode *root;
	STree(ushort *_kList, int _nKeys) 
		: keyList(_kList), nKeys(_nKeys) {
		root = new SNode(0, 0, 0, nKeys-1, keyList);
	}
	ushort getMaxXor(ushort key, int low, int high) {
		return getMaxXor(root, key, low, high);
	}
	ushort getMaxXor(SNode *cur, ushort key, int low, int high) {
		if(!cur || cur->high < low || cur->low > high) return 0;
		if(cur->low >= low && cur->high <= high)
			return cur->getMaxXor(key);
		int mid = (cur->low + cur->high)/2;
		if(low <= mid && !cur->left)
			cur->left = new SNode(0,0,cur->low,mid,keyList);
		if(high > mid && !cur->right) 
			cur->right = new SNode(0,0,mid+1,cur->high,keyList);
		if(high <= mid) return getMaxXor(cur->left, key, low, high);
		if(low > mid) return getMaxXor(cur->right, key, low, high);
		ushort lmax = getMaxXor(cur->left, key, low, high);
		ushort rmax = getMaxXor(cur->right, key, low, high);
		return max(lmax, rmax);
	}
};

void solveXORKey() {
	int nTests; scanf(" %d", &nTests);
	for(int test = 0; test < nTests; test++) {
		int nKeys, nQuery; scanf(" %d %d", &nKeys, &nQuery);
		ushort *keyList = new ushort[nKeys];
		for(int index = 0; index < nKeys; ++index)
			scanf(" %hu", &keyList[index]);

		STree tree(keyList, nKeys);
		ushort key; int low, high;
		for(int query = 0; query < nQuery; ++query) {
			scanf(" %hu %d %d", &key, &low, &high);
			printf("%hu\n", tree.getMaxXor(key, low-1, high-1));
		}
	}
}

int main(int argc, char *argv[]) {
	solveXORKey();
	return 0;
}
