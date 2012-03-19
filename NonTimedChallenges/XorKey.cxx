// XOR key
// 
// Xorq has invented an encryption algorithm which uses bitwise XOR 
// operations extensively. This encryption algorithm uses a sequence of 
// non-negative integers x1, x2, ... xn  as key. To implement this algorithm 
// efficiently, Xorq needs to find maximum value for (a xor xj)  for given 
// integers a,p and q such that p<=j<=q. Help Xorq to implement this 
// function.
// 
// Input
// First line of input contains a single integer T (1<=T<=6). T test cases 
// follow.
// 
// First line of each test case contains two integers N and Q separated by a 
// single space (1<= N<=100,000; 1<=Q<= 50,000).  Next line contains N 
// integers x1, x2, ... xn separated by a single space (0<=xi< 215). Each of 
// next Q lines describe a query which consists of three integers ai,pi and 
// qi (0<=ai< 215, 1<=pi<=qi<= N).
// 
// Output
// For each query, print the maximum value for (ai xor xj) such that pi<=j<=qi  
// in a single line.
// 
// Sample Input
// 1
// 15 8
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// 10 6 10
// 1023 7 7
// 33 5 8
// 182 5 10
// 181 1 13
// 5 10 15
// 99 8 9
// 33 10 14
// 
// Sample Output
// 13
// 1016
// 41
// 191
// 191
// 15
// 107
// 47
// 
// Explanation
// First Query (10 6 10): x6 xor 10 = 12, x7 xor 10 = 13, x8 xor 10 = 2, 
// x9 xor 10 = 3, x10 xor 10 = 0, therefore answer for this query is 13.
// Second Query (1023 7 7): x7 xor 1023 = 1016, therefore answer for this 
// query is 1016.
// Third Query (33 5 8): x5 xor 33 = 36, x6 xor 33 = 39, x7 xor 33 = 38, 
// x8 xor 33 = 41, therefore answer for this query is 41.
// Fourth Query (182 5 10): x5 xor 182 = 179, x6 xor 182 = 176, 
// x7 xor 182 = 177, x8 xor 182 = 190, x9 xor 182 = 191, x10 xor 182 = 188, 
// therefore answer for this query is 191.

// The solution is to build a binary tree with height 15, where the decision
// of going left or right is based on whether the bit at that height is 1/0.
// Store all the indices which belong to that bit depth in that node. You can
// do a binary search for the required interval using this tree.

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

