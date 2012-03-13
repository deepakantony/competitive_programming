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

void printPointVec(const vector<Point> &v) {
	for(auto it = v.begin(); it != v.end(); ++it)
		cout << "(" << it->x << ", " << it->y << ")" << endl;
}

// Interval node
struct INode 
{
	int low, high, mid; // intervals inclusive
	INode *left, *right, *parent;
	bool updated;
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
		cur->mid = (low+high)/2;
		cur->left = cur->right = 0;
		cur->parent = parent;
		cur->updated = true;

		if(cur->low == cur->high)
			cur->result = pointData[cur->low].quadrantInfo;
		else {
			cur->left = constructITree(low, cur->mid, cur);
			cur->right = constructITree(cur->mid + 1, high, cur);
			cur->result = new int[4];
			add(cur->left->result, cur->right->result, cur->result);
		}
		return cur;
	}
	void getQuadrantInfo(int i, int j, int *qInfo) {
		fill(qInfo, qInfo+4, 0);
		getInfo(i, j, qInfo);
	}

	void getInfo(int i, int j, int *qInfo) {
		if(!root) return;
		
		vector<INode*> stack;
		stack.push_back(root);

		while(stack.size() > 0) {
			INode *cur = stack.back();
			stack.pop_back();
			if(cur->low >= i && cur->high <= j)
				add(cur->result, qInfo);
			else {
				if(i > cur->mid) 
					stack.push_back(cur->right);
				else if(j <= cur->mid)
					stack.push_back(cur->left);
				else {
					stack.push_back(cur->right);
					stack.push_back(cur->left);
				}
			}
		}
	}

	void getInfo(INode *cur, const int &i, const int &j, int *qInfo) {
		if(!cur) return;

		if(cur->low == i && cur->high == j) {
			add(cur->result, qInfo);
			return;
		}

		if(i > cur->mid) return getInfo(cur->right, i, j, qInfo);
		if(j <= cur->mid) return getInfo(cur->left, i, j, qInfo);
		
		getInfo(cur->right, cur->mid+1, j, qInfo);
		getInfo(cur->left, i, cur->mid, qInfo);
	}

	void reflectX(int i, int j) {
		XorY = 1;
		reflect(root, i, j);
	}

	void reflectY(int i, int j) {
		XorY = 0;
		reflect(root, i, j);
	}

	void ref(Point *p) {
		if( XorY )
			p->reflectX();
		else
			p->reflectY();
	}
/*
	void reflect(int i, int j) {
		if(!root) return;
		vector<INode*> stack;
		root->updated = false;
		stack.push_back(root);
		while(stack.size() > 0) {
			INode *cur = stack.back();
			if(cur->low == cur->high) {
				stack.pop_back();
				ref(&pointData[cur->low]);
				cur->updated = true;
			}
			else {
				if(i > cur->mid) {
					cur->right->updated = false;
					stack.push_back(cur->right);
				}
				else if(j <= cur->mid) {
					cur->left->updated = false;
					stack.push_back(cur->left);
				}
				else if(
			}
		}
		}*/

	void reflect(INode* cur, int i, int j) {
		if(!cur) return;
		if(cur->low == cur->high) { 
			ref(&pointData[cur->low]); return; 
		}

		if(i > cur->mid) reflect(cur->right, i, j);
		else if(j <= cur->mid) reflect(cur->left, i, j);
		else {
			reflect(cur->left, i , cur->mid);
			reflect(cur->right, cur->mid+1, j);
		}
		add(cur->left->result, cur->right->result, cur->result);
	}

	INode *root;
	vector<Point> &pointData;
	int XorY;
};

void solveQuadrantQueries()
{
	int nPoints;
	vector<Point> pointData;
	scanf("%d", &nPoints);
	for(int point = 0; point < nPoints; ++point)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		pointData.push_back( Point(x,y));
	}
	ITree intervalTree(pointData);
	int nQueries;
	scanf("%d", &nQueries);
	int *q = new int[4];

	for(int query = 0; query < nQueries; ++query)
	{
		char action;
		int i, j;
		scanf(" %c %d %d", &action, &i, &j);

		switch (action) {
		case 'C':
			intervalTree.getQuadrantInfo(i-1,j-1,q);
			printQuadrant(q);
			break;
		case 'X':
			intervalTree.reflectX(i-1, j-1);
			break;
		case 'Y':
			intervalTree.reflectY(i-1, j-1);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	solveQuadrantQueries();
	return 0;
}

