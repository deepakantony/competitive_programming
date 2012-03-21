#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef unsigned short ushort;

bool isNthBitOn(ushort n, int pos) { return ((n & (1 << pos)) != 0); }
ushort flipBit(ushort n, int bitPosition)
{ // flip the bit at given position
	return ((~n) & (1<<bitPosition)) | ((n) & (~(1<<bitPosition)));
}


struct BNode {
	BNode(BNode *l, BNode *r) 
		: left(l), right(r) {}
	BNode *left, *right;
};
struct BTree {
	BTree() { root = new BNode(0,0); }
	void insert(int x) {
		BNode *cur = root;
		for(int bitPos = 15; bitPos >= 0; --bitPos) {
			if(isNthBitOn(x, bitPos)) {
				// insert to the right
				if(!cur->right) 
					cur->right = new BNode(0,0);
				cur = cur->right;
			}
			else {
				if(!cur->left)
					cur->left = new BNode(0,0);
				cur = cur->left;
			}
		}
	}
	ushort getMaxXor(ushort key) {
		BNode *cur = root;
		ushort keyNeg = ~key;
		for(int bitPos = 15; bitPos >= 0; --bitPos) {
			if(isNthBitOn(keyNeg, bitPos)) {
				if(cur->right) cur = cur->right;
				else { 
					keyNeg = flipBit(keyNeg, bitPos);
					cur = cur->left;
				}
			}
			else {
				if(cur->left) cur = cur->left;
				else {
					keyNeg = flipBit(keyNeg, bitPos);
					cur = cur->right;
				}
			}
		}
		return keyNeg^key;
	}
	~BTree() {
		recurseDelete(root);
	}
	void recurseDelete(BNode *cur) {
		if(cur->left) recurseDelete(cur->left);
		if(cur->right) recurseDelete(cur->right);
		delete cur;
	}

	BNode *root;
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
	}
	ushort getMaxXor(ushort key) {
		return setOfKeys->getMaxXor(key);
	}
	void print() {
		printf("[%d %d]\n(", low, high);
		
		printf(")\n");
	}
	~SNode() {
		delete setOfKeys;
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
	~STree() {
		deleteRecurse(root);
	}
	void deleteRecurse(SNode *cur) {
		if(cur->left) deleteRecurse(cur->left);
		if(cur->right) deleteRecurse(cur->right);
		delete cur;
	}
};

void solveXORKey() {
	int nTests; scanf(" %d", &nTests);
	for(int test = 0; test < nTests; test++) {
		int nKeys, nQuery; scanf(" %d %d", &nKeys, &nQuery);
		ushort *keyList = new ushort[nKeys];
		for(int index = 0; index < nKeys; ++index)
			scanf(" %hu", &keyList[index]);

		STree *tree = new STree(keyList, nKeys);
		ushort key; int low, high;
		for(int query = 0; query < nQuery; ++query) {
			scanf(" %hu %d %d", &key, &low, &high);
			printf("%hu\n", tree->getMaxXor(key, low-1, high-1));
		}
		//delete tree;
		delete []keyList;
	}
}

int main(int argc, char *argv[]) {
	solveXORKey();
	return 0;
}
