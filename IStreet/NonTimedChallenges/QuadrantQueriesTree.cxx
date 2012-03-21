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
	void reflectX() { reflectQX(quadrantInfo); }
	void reflectY() { reflectQY(quadrantInfo); }
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
	INode *left, *right;
	int *result;
};

struct ITree
{
	ITree(vector<Point> &_pointData) : pointData(_pointData) { 
		root = constructITree(0, pointData.size()-1); 
		resetUpdateLowHigh();
	}

	void resetUpdateLowHigh() {
		updateLow = pointData.size();
		updateHigh = -1;
		updated = false;
	}

	INode* constructITree(int low, int high) {
		INode *cur = new INode;
		cur->low = low; cur->high = high;
		cur->mid = (low+high)/2;
		cur->left = cur->right = 0;
		if(cur->low == cur->high)
			cur->result = pointData[cur->low].quadrantInfo;
		else {
			cur->left = constructITree(cur->low, cur->mid);
			cur->right = constructITree(cur->mid + 1, cur->high);
			cur->result = new int[4];
			add(cur->left->result, cur->right->result, cur->result);
		}
		return cur;
	}
	void getQuadrantInfo(int i, int j, int *qInfo) {
		fill(qInfo, qInfo+4, 0);
		if(i<j && updated) {
			int curI = i, curJ = j;
			if(i <= updateLow)
				curI = updateLow;
			if(j >= updateHigh)
				curJ = updateHigh;
			update(root, curI, curJ);
		}
		if(updated) {
			if(i <= updateLow)
				if (j >= updateHigh) resetUpdateLowHigh(); else updateLow = j;
			else if (j >= updateHigh)
				updateHigh = i;
		}

		getInfo(root, i, j, qInfo);
	}

	void getInfo(INode *cur, int i, int j, int *qInfo) {
		if(!cur) return;

		if(cur->low == i && cur->high == j) {
			add(cur->result, qInfo);
			return;
		}

		if(i > cur->mid) return getInfo(cur->right, i, j, qInfo);
		if(j <= cur->mid) return getInfo(cur->left, i, j, qInfo);
		
		getInfo(cur->right,cur->mid+1, j, qInfo);
		getInfo(cur->left, i, cur->mid, qInfo);
	}

	void reflectX(int i, int j) {
		XorY = 1;
		if(i<updateLow) { updateLow = i; updated = true; }
		if(j>updateHigh) { updateHigh = j; updated = true; }
		fastreflect(i, j);
	}

	void reflectY(int i, int j) {
		XorY = 0;
		if(i<updateLow) { updateLow = i; updated = true; }
		if(j>updateHigh) { updateHigh = j; updated = true; }
		fastreflect(i, j);
	}

	void ref(Point *p) {
		if( XorY )
			p->reflectX();
		else
			p->reflectY();
	}

	void ref(int *q) { // quadrant
		if( XorY )
			reflectQX(q);
		else
			reflectQY(q);
	}

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

	void fastreflect(int i, int j) {
		for(int index = i; index <= j; index++)
			ref(&pointData[index]);
	}

	void update(INode* cur, int i, int j) {
		if(!cur || cur->low == cur->high) return;

		if(cur->low + 1 == cur->high) {
			add(cur->left->result, cur->right->result, cur->result);
			return;
		}			

		else if(i > cur->mid) update(cur->right, i, j);
		else if(j <= cur->mid) update(cur->left, i, j);
		else {
			update(cur->right, cur->mid+1, j);
			update(cur->left, i, cur->mid);
		}
		add(cur->left->result, cur->right->result, cur->result);
	}
	
	void swapUpdate(INode *cur) {
		if(cur->low == cur->high) return;
		if(cur->low+1 == cur->high) {
			ref(cur->result);
			return;
		}
		swapUpdate(cur->left);
		swapUpdate(cur->right);
		ref(cur->result);
	}

	INode *root;
	vector<Point> &pointData;
	int XorY;
	int updateLow, updateHigh;
		   bool updated;
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
		int i, j;
		char action;
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
