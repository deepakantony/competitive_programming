#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef unsigned short ushort;

bool isNthBitOn(ushort n, int pos) { return ((n & (1 << pos)) != 0); }
ushort flipBit(ushort n, int bitPosition)
{ // flip the bit at given position
	return ((~n) & (1<<bitPosition)) | ((n) & (~(1<<bitPosition)));
}

void printVec(vector<int> vec, ushort *keyList){
	printf("( ");
	for(auto entry: vec)
		printf("[%d, %d] ", entry, keyList[entry]);
	printf(" )\n");
}


struct BNode {
	BNode(BNode *l, BNode *r) 
		: left(l), right(r) {}
	BNode *left, *right;
	vector<int> indexVec;
};
struct BTree {
	BTree(ushort *_keyList, int _nKeys)
		:keyList(_keyList), nKeys(_nKeys){ 
		root = new BNode(0,0);

		for(int key = 0; key < nKeys; key++) {
			BNode *cur = root;
			for(int bitPos = 14; bitPos >= 0; bitPos--) {
				if(isNthBitOn(keyList[key], bitPos)) {
					if(!cur->right) cur->right = new BNode(0,0);
					cur = cur->right;
					cur->indexVec.push_back(key);
				}
				else {
					if(!cur->left) cur->left = new BNode (0,0);
					cur = cur->left;
					cur->indexVec.push_back(key);
				}
			}
		}
	}

	ushort getMaxXor(ushort key, int low, int high) {
		ushort maxXor = flipBit(~key, 15);
		BNode *cur = root;

		for(int bitPos = 14; bitPos >= 0; bitPos--) {		
			if(isNthBitOn(maxXor, bitPos)) {
				if(cur->right && findInterval(cur->right, low, high)) {
					cur = cur->right;
				}
				else {
					maxXor = flipBit(maxXor, bitPos);
					cur = cur->left;
				}
			}
			else {
				if(cur->left && findInterval(cur->left, low, high)) {
					cur = cur->left;
				}
				else {
					maxXor = flipBit(maxXor, bitPos);
					cur = cur->right;
				}
			}
		}

		return maxXor ^ key;
	}

	bool findInterval(BNode *cur, int low, int high) {
		if(!cur) return false;
		int l = 0, r = cur->indexVec.size()-1;
		while(l <= r) {
			int mid = (l+r)/2;
			int midInd = cur->indexVec[mid];
			if(midInd >= low && midInd <= high)
				return true;
			if(midInd > high)
				r = mid-1;
			else // if(midInd < low)
				l = mid+1;
		}
		return false;
	}

	void print() { print(root, "ROOT"); }
	void print(BNode *cur, const char *msg) {
		if(!cur) return;
		printf("%s\n", msg);
		printVec(cur->indexVec, keyList);
		print(cur->left, "LEFT");
		print(cur->right, "RIGHT");
	}
	BNode *root;
	ushort *keyList;
	int nKeys;
};

void solveXORKey() {
	int nTests; scanf(" %d", &nTests);
	ushort *keyList = new ushort[100001];
	for(int test = 0; test < nTests; test++) {
		int nKeys, nQuery; scanf(" %d %d", &nKeys, &nQuery);

		for(int index = 0; index < nKeys; ++index)
			scanf(" %hu", &keyList[index]);

		BTree *tree = new BTree(keyList, nKeys);
		ushort key; int low, high;
		for(int query = 0; query < nQuery; ++query) {
			scanf(" %hu %d %d", &key, &low, &high);
			printf("%hu\n", tree->getMaxXor(key, low-1, high-1));
		}
		//delete tree;

	}
}

int main(int argc, char *argv[]) {
	solveXORKey();
	return 0;
}

