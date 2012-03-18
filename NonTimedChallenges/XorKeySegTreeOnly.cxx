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
	vector<ushort> sortedSet;
	int setSize;

	SNode(SNode *l, SNode *r, int _low, int _high, ushort *_list) 
		: left(l), right(r), low(_low), high(_high) {
		mid = (low+high)/2;
		unordered_set<ushort> s;
		for(int index = low; index <= high; ++index)
			s.insert(_list[index]);
		setSize = s.size();
		//sortedSet = new ushort[setSize];
		int index = 0;
		for(auto it = s.begin(); it != s.end(); ++it)
			sortedSet.push_back(*it);
		//sort(sortedSet, sortedSet+setSize);
	}



	void print() {
		printf("[%d, %d] - ", low, high);
		for(int index = 0; index < setSize; ++index)
			printf("%d, ", sortedSet[index]);
		printf("\n");
	}

	ushort getMaxXor(ushort key) {
		ushort max = 0;
		for(auto it = sortedSet.begin(); it != sortedSet.end(); ++it) {
			ushort temp = (*it) ^ key;
			if(temp > max)
				max = temp;
		}
		return max;
	}
			
			

	ushort getMaxXor2(ushort key) {
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
			//printf("****** [%d %d] ****** [", first, last);
			//for(int i = first; i <= last; i++)
			//printf("%d, ", sortedSet[i]);
			//printf("] - %s\n", decToBinary(key).c_str());
			
		}
		//printf("****** [%d %d] ******", first, last);
		return (sortedSet[first] ^ key);
	}

	int findLowerBound(int first, int last, int bitPos) {
		//printf("Finding lower bound\n");
		int curLow = first;
		while(first <= last) {
			int mid = (first+last)/2;
			//printf("*** %d %d %s ***\n", sortedSet[mid], bitPos, decToBinary(sortedSet[mid]).c_str());
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

				last = mid - 1;
			}
			else {
				curHigh = mid;
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
		root = simpleCreate(0, nKeys-1);
		//root = recurseCreateTree(0, nKeys-1);
	}

	~SegmentTree() {
		recurseDeleteTree(root);
	}

	ushort getMaxXor(ushort key, int l, int h) {
		return getMaxXor2(root, key, l, h);
	}

	void print() { print(root); }
private:
	ushort getMaxXor2(SNode *cur, ushort key, int l, int h) {
/*		if(l > h) {
			printf("HOW DID THIS HAPPEN\n");
			return 0;
			}*/
		if(cur->low >= l && cur->high <= h)  {
			//ushort res = cur->getMaxXor(key);
			//printf("(%d %d %d)\n", res, key, res^key);
			//cur->print();
			return cur->getMaxXor(key);
		}
/*
		//if(l <= cur->mid && !cur->left) 
		if(!cur->left)
		
		 	cur->left = simpleCreate(cur->low, cur->mid);
		//if(h > cur->mid && !cur->right)
		if(!cur->right)
			cur->right = simpleCreate(cur->mid+1, cur->high);
*/
		ushort lmax = 0, rmax = 0;
		if(l > cur->mid) {
			if(!cur->right)
				cur->right = simpleCreate(cur->mid+1, cur->high);
			return getMaxXor2(cur->right, key, l, h);
		}
		else if(h <= cur->mid) {
			if(!cur->left)
				cur->left = simpleCreate(cur->low, cur->mid);
			return getMaxXor2(cur->left, key, l, h);
		}
		else {
/*		if(l <= cur->mid)
			lmax = getMaxXor2(cur->left, key, l, h);
		if(h > cur->mid)
		rmax = getMaxXor2(cur->right, key, l, h);*/
			if(!cur->left)
				cur->left = simpleCreate(cur->low, cur->mid);
			if(!cur->right)
				cur->right = simpleCreate(cur->mid+1, cur->high);
				
			lmax = getMaxXor2(cur->left, key, l, cur->mid);
			rmax = getMaxXor2(cur->right, key, cur->mid+1, h);
			return lmax > rmax ? lmax : rmax;

		}
	}

	void recurseDeleteTree(SNode *cur) {
		if(cur) {
			recurseDeleteTree(cur->left);
			recurseDeleteTree(cur->right);
			delete cur;
		}
	}
	
	SNode* simpleCreate(int low, int high) {
			return new SNode(0, 0, low, high, keyList);
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
		if(l > cur->mid) 
			return getMaxXor(cur->right, key, l, h);
		else if(h <= cur->mid)
			return getMaxXor(cur->left, key, l, h);
		ushort lMax = getMaxXor(cur->left, key, l, h);
		ushort rMax = getMaxXor(cur->right, key, l, h);
		return max(lMax, rMax);
	}

	SNode *root;
	ushort *keyList;
	int nKeys;
};

ushort naiveImpl(ushort key, ushort *keyList, int l, int h) {
	ushort max = 0;
	for(int index = l; index <= h; ++index)
	{
		ushort temp = keyList[index] ^ key;
		if(temp > max) max = temp;
	}
	return max;
}

void printInfo(ushort *keyList, int low, int high, 
			   ushort key, ushort res1, ushort res2) {
	printf("**********************************************************\n");
	printf("low: %d, high: %d, treeres: %hu, naive: %hu, key: %hu\n",
		   low, high, res1, res2, key);
	for(int index = low; index <= high; ++index)
		printf("[%hu %hu %hu %d]\n", key, keyList[index], keyList[index]^key, index);
}

void runTreeTest(SegmentTree *tree, ushort *keyList, ushort key,
				 int low, int high) {
	ushort res1 = tree->getMaxXor(key, low, high);
	ushort res2 = naiveImpl(key, keyList, low, high);
	if(res1 != res2) {
		tree->print();
		printInfo(keyList, low, high, key, res1, res2);
	}
}

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
	
	int size = 100000;
	for(int test = 0; test < 6; ++test) {
		ushort *keyList = new ushort[size];
		for(int key = 0; key < size; key++)
			keyList[key] = rand() % 65536;
		SegmentTree *tree = new SegmentTree(keyList, size);

/*
		for(int query = 0; query < 5000; ++query) {
			ushort key = rand() % 65536;
			int low = rand() % size, high = low + rand() % (size-low);
			runTreeTest(tree, keyList, key, low, high);
			}*/
		runTreeTest(tree, keyList, 12345, 0, size-1);
		runTreeTest(tree, keyList, 12345, 0, size-1/2);
		runTreeTest(tree, keyList, 12345, ((size-1)/2)+1, size-1);
		runTreeTest(tree, keyList, 12345, ((size-1)/2)+1, (size-1)*3/4);
		runTreeTest(tree, keyList, 12345, size-1, size-1);
		delete tree;
		delete [] keyList;
	}
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
	unitTest();
//  solveXorKey();
	return 0;
}

