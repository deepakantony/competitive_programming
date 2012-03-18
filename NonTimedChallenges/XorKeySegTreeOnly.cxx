#include <iostream>
#include <string>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef unsigned short ushort;

ushort flipShort(ushort n)
{ // flips bits and 0's out last bit
	return (~n) & (0xFFFF >> 1);
}

ushort flipBit(ushort n, int bitPosition)
{ // flip the bit at given position
	return ((~n) & (1<<bitPosition)) | ((n) & (~(1<<bitPosition)));
}

string decToBinary(ushort n)
{ // convert decimal to binary
	string binary;
	while(n > 0)
	{
		binary += '0'+n%2;
		n /= 2;
	}
	while(binary.size() < 16)
		binary += '0';
	reverse(binary.begin(), binary.end());
	return binary;
}

bool isNthBitOn(ushort n, int bitPosition) {
	return n & (1<<bitPosition);
}

struct SNode {
	SNode *left, *right;
	int low, high, mid;
	ushort *sortedSet;
	int setSize;

	SNode(SNode *l, SNode *r, int _low, int _high, ushort *_list) 
		: left(l), right(r), low(_low), high(_high), mid((_low+_high)/2) {
		unordered_set<ushort> s;
		for(int index = low; index <= high; ++index)
			s.insert(_list[index]);
		setSize = s.size();
		sortedSet = new ushort[setSize];
		int index = 0;
		for(auto it = s.begin(); it != s.end(); ++it)
			sortedSet[index++] = *it;
		sort(sortedSet, sortedSet+setSize);
	}

	~SNode() {
		delete []sortedSet;
	}

	void print() {
		printf("[%d, %d] - ", low, high);
		for(int index = 0; index < setSize; ++index)
			printf("%d, ", sortedSet[index]);
		printf("\n");
	}

	ushort getMaxXor(ushort key) {
		if(setSize == 1)
			return (sortedSet[0] ^ key);
		if(setSize == 2)
			return max((sortedSet[0] ^ key), (sortedSet[1] ^ key));

		int first =0, last = setSize-1;
		for(int bit = 15; bit >= 0 && first < last; bit--) {
			if(isNthBitOn(key, bit))
				last = findUpperBound(first, last, bit);
			else
				first = findLowerBound(first,last, bit);
			/*printf("****** [%d %d] ****** [", first, last);
			for(int i = first; i <= last; i++)
				printf("%d, ", sortedSet[i]);
			printf("] - %s\n", decToBinary(key).c_str());
			*/
		}
		//printf("****** [%d %d] ******", first, last);
		return sortedSet[first] ^ key;
	}

	int findLowerBound(int first, int last, int bitPos) {
		//	printf("Finding lower bound\n");
		int curLow = first;
		while(first <= last) {
			int mid = (first+last)/2;
			//	printf("*** %d %d %s ***\n", sortedSet[mid], bitPos, decToBinary(sortedSet[mid]).c_str());
			if(isNthBitOn(sortedSet[mid], bitPos)) {

				curLow = mid;
				last = mid - 1;
			}
			else {
				first = mid + 1;
			}
		}
		return curLow;
	}

	int findUpperBound(int first, int last, int bitPos) {
		//printf("Finding upper bound\n");
		int curHigh = last;
		while(first <= last) {
			int mid = (first+last)/2;
			//printf("*** %d %d %s ***\n", sortedSet[mid], bitPos, decToBinary(sortedSet[mid]).c_str());
			if(isNthBitOn(sortedSet[mid], bitPos)) {
				curHigh = mid;
				last = mid - 1;
			}
			else {
				first = mid+1;
			}
		}
		return curHigh;
	}

};

class SegmentTree {
public:
	SegmentTree(ushort *_keyList, int _nKeys) 
		: keyList(_keyList), nKeys(_nKeys) {
		root = recurseCreateTree(0, nKeys-1);
	}

	~SegmentTree() {
		recurseDeleteTree(root);
	}

	ushort getMaxXor(ushort key, int l, int h) {
		return getMaxXor(root, key, l, h);
	}

	void print() { print(root); }
private:
	void recurseDeleteTree(SNode *cur) {
		if(cur) {
			recurseDeleteTree(cur->left);
			recurseDeleteTree(cur->right);
			delete cur;
		}
	}

	SNode *recurseCreateTree(int low, int high) {
		if(low == high)
			return new SNode(0, 0, low, high, keyList);
		else {
			int mid = (low + high)/2;
			SNode *l = recurseCreateTree(low, mid);
			SNode *r = recurseCreateTree(mid+1, high);
			return new SNode(l, r, low, high, keyList);
		}
	}

	void print(SNode *cur) { 
		if(cur) {
			cur->print(); print(cur->left); print(cur->right);
		}
	}
	
	ushort getMaxXor(SNode *cur, ushort key, int l, int h) {
		if(!cur) return 0;
		if(cur->low >= l && cur->high <= h) {
			/*ushort res = cur->getMaxXor(key);
			printf("(%d %d %d)\n", res, key, res^key);
			cur->print();*/
			return cur->getMaxXor(key);
		}
		if(cur->low > cur->mid) 
			return getMaxXor(cur->right, key, l, h);
		else if(cur->high <= cur->mid)
			return getMaxXor(cur->left, key, l, h);
		ushort lMax = getMaxXor(cur->left, key, l, h);
		ushort rMax = getMaxXor(cur->right, key, l, h);
		return max(lMax, rMax);
	}

	SNode *root;
	ushort *keyList;
	int nKeys;
};


void unitTest()
{
	// flipShort function
	ushort ten = 10, three = 3, two =2, four = 4;
	assert(flipShort((ushort)10) != ~ten);
	assert(flipShort(10) == (~ten & (0x7FFF)));
	assert(flipShort(three) == (ushort)32764);

	// flipBit function
	assert(flipBit(4, 3) == (ushort)12);
	assert(flipBit(0, 10) == (ushort)(1<<10));

	// decToBinary functionxs
	assert(decToBinary(2) == string("0000000000000010"));
	assert(decToBinary(32764) == string("0111111111111100"));
}

void solveXorKey() 
{
	int nTests, nKeys, nQueries;
	scanf(" %d", &nTests);
	scanf(" %d %d", &nKeys, &nQueries);
	for(int test = 0; test < nTests; ++test) {
		ushort *keyList = new ushort[nKeys];

		for(int key = 0; key < nKeys; ++key)
			scanf(" %hu", &keyList[key]);
		SegmentTree *tree = new SegmentTree(keyList, nKeys);
		ushort key;
		int low, high;
		//tree->print();
		for(int query = 0; query < nQueries; ++query) {
			scanf(" %hu %d %d", &key, &low, &high);

			printf("%hu\n", tree->getMaxXor(key, low-1, high-1));
		}
		delete tree;
		delete [] keyList;
	}
}

int main(int argc, char *argv[])
{
//	unitTest();
	solveXorKey();
	return 0;
}
			
