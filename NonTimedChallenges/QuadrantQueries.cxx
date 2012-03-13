#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

void findQuadrandInfo(int x, int y, int *quadrantInfo) {
	fill(quadrantInfo, quadrantInfo+4, 0);
	if(x >= 0)
		y >= 0 ? quadrantInfo[0] = 1 : quadrantInfo[3] = 1;
	else
		y >= 0 ? quadrantInfo[1] = 1 : quadrantInfo[2] = 1;
}

void add(int *q1, int *q2, int *sum) {
	sum[0] = q1[0] + q2[0]; 
	sum[1] = q1[1] + q2[1];
	sum[2] = q1[2] + q2[2]; 
	sum[3] = q1[3] + q2[3];
}

void add(int *q1, int *sum) {
	sum[0] += q1[0];
	sum[1] += q1[1];	
	sum[2] += q1[2];
	sum[3] += q1[3];
}

void reflectQX(int *q) {
	swap(q[0], q[3]);
	swap(q[1], q[2]);
}

void reflectQY(int *q) {
	swap(q[0], q[1]);
	swap(q[3], q[2]);
}

void printQuadrant(int *q) {
	printf("%d %d %d %d\n", q[0], q[1], q[2], q[3]);
}

struct Point { 
	Point(int _x, int _y) : x(_x), y(_y) {
		quadrantInfo = new int[4];
		findQuadrandInfo(x, y, quadrantInfo);
	}
	void reflectX() { y = -y; reflectQX(quadrantInfo); }
	void reflectY() { x = -x; reflectQY(quadrantInfo); }
	int x, y; 
	int *quadrantInfo;
};

// Interval node
struct INode 
{
	int low, high; // intervals inclusive
	INode *left, *right, *parent;
	int *result;
};

struct ITree
{
	ITree(vector<Point> &_pointData) : pointData(_pointData) { 
		root = constructITree(0, pointData.size()-1, 0); 
	}
	INode* constructITree(int low, int high, INode *parent) {
		INode *cur = new INode;
		cur->low = low; cur->high = high;
		cur->left = cur->right = 0;
		cur->parent = parent;
		if(cur->low == cur->high)
			cur->result = pointData[cur->low].quadrantInfo;
		else {
			cur->left = constructITree(low, (low+high)/2, cur);
			cur->right = constructITree(((low+high)/2)+ 1, high, cur);
			cur->result = new int[4];
			add(cur->left->result, cur->right->result, cur->result);
		}
		return cur;
	}
	void getQuadrantInfo(int i, int j, int *qInfo) {
		fill(qInfo, qInfo+4, 0);
		getInfo(root, i, j, qInfo);
	}

	void getInfo(INode *cur, int i, int j, int *qInfo) {
		if(!cur) return;
		if(cur->low == i && cur->high == j) {
			add(cur->result, qInfo);
			return;
		}
		int mid = (cur->low + cur->high)/2;
		if(i > mid) return getInfo(cur->right, i, j, qInfo);
		if(j <= mid) return getInfo(cur->left, i, j, qInfo);
		
		getInfo(cur->right, mid+1, j, qInfo);
		getInfo(cur->left, i, mid, qInfo);
	}
	INode *root;
	vector<Point> &pointData;
};

void solveQuadrantQueries()
{
	int nPoints;
	vector<Point> pointData;
	scanf("%d", &nPoints);
	for(int point = 0; point < nPoints; ++point)
	{
		int x, y;
		scanf("%d", &x);
		scanf("%d", &y);
		pointData.push_back( Point(x,y));
	}
	ITree intervalTree(pointData);
	int nQueries;
	scanf("%d", &nQueries);
	int *q = new int[4];
	for(int query = 0; query < nQueries; ++query)
	{
		int i, j;
		char action;
		cin >> action >> i >> j;

		if(action == 'C') {
			intervalTree.getQuadrantInfo(i-1,j-1,q);
			printQuadrant(q);
		}
	}
}

int main(int argc, char *argv[])
{
	solveQuadrantQueries();
	return 0;
}

