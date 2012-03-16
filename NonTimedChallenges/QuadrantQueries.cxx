#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <ctime>

using namespace std;


void printQuadrant(int *q) {
	printf("%d %d %d %d\n", q[0], q[1], q[2], q[3]);
}


void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

void flip(bool &flag) {
	flag = flag ? false:true;
}

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
	int low, high; // intervals inclusive
	bool X, Y;
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
		cur->X = cur->Y = 0;
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

		if(needsUpdate(cur))
			update(cur);

		if(cur->low >= i && cur->high <= j) {
			add(cur->result, qInfo);
			return;
		}
		int mid = (cur->low + cur->high)/2;
		if(i > mid) return getInfo(cur->right, i, j, qInfo);
		if(j <= mid) return getInfo(cur->left, i, j, qInfo);
		
		getInfo(cur->right, mid+1, j, qInfo);
		getInfo(cur->left, i, mid, qInfo);
	}

	void reflectX(int i, int j) {
		reflect(root, i, j, 1);
	}

	void reflectY(int i, int j) {
		reflect(root, i, j, 0);
	}

	void ref(Point *p, int i) {
		if( i )
			p->reflectX();
		else
			p->reflectY();
	}

	void ref(int *q, int i) {
		if(i)
			reflectQX(q);
		else reflectQY(q);
	}

	void reflect(INode* cur, int i, int j, int XorY) {
		if(!cur) return;
		if(cur->low >= i && cur->high <= j) {
			propagate(cur, XorY);
			update(cur);
			return;
		}
		if(needsUpdate(cur)) {
			update(cur);
		}

		int mid = (cur->low + cur->high)/2;
		if(i > mid) {
			reflect(cur->right, i, j, XorY);
		}
		else if(j <=mid) {
			reflect(cur->left, i, j, XorY);
		}
		else {
			reflect(cur->left, i , mid, XorY);
			reflect(cur->right, mid+1, j, XorY);
		}
		if(needsUpdate(cur->left))
			update(cur->left);
		if(needsUpdate(cur->right))
			update(cur->right);
		add(cur->left->result, cur->right->result, cur->result);
		clearUpdateFlag(cur);
	}

	bool needsUpdate(INode *n) {
		return n->X || n->Y;
	}

	void propagate(INode *fromNode, INode *toNode) {
		if(fromNode->X)
			toNode->X = !toNode->X;
		if(fromNode->Y)
			toNode->Y = !toNode->Y;
	}
	void propagate(INode *n, int X) {
		if(X)
			n->X = !n->X;
		else
			n->Y = !n->Y;
	}
	void swapupdate(INode *n) {
//		if(n->X) {printf("[%d, %d] - true", n->low, n->high); printQuadrant(n->result); }
//		else {printf("[%d, %d] - false", n->low, n->high); printQuadrant(n->result); }
		if(n->X)
			reflectQX(n->result);
		if(n->Y)
			reflectQY(n->result);
//		printQuadrant(n->result);
	}

	void update(INode *cur) {
		swapupdate(cur);
		if(cur->left)
			propagate(cur, cur->left);
		if(cur->right)
			propagate(cur, cur->right);
		clearUpdateFlag(cur);
	}
	void clearUpdateFlag(INode *n) {
		n->X = n->Y = false;
	}
	void print() { print(root); }
	void print(INode *cur) {
		if(!cur) return;
		printf("[%d, %d] ", cur->low, cur->high);
		printQuadrant(cur->result);
		print(cur->left);
		print(cur->right);
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
		scanf("%d %d", &x, &y);
		pointData.push_back( Point(x,y));
	}
	ITree intervalTree(pointData);
	int nQueries;
	scanf("%d", &nQueries);
	int *q = new int[4];
	for(int query = 0; query < nQueries; ++query)
	{
		//intervalTree.print();
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
		//printPointVec(intervalTree.pointData);
	}
}

int main(int argc, char *argv[])
{
	solveQuadrantQueries();
	return 0;
}
