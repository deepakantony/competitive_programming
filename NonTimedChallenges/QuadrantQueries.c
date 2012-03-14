#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b; *b = temp; 
}

void findQuadrandInfo(int x, int y, int *quadrantInfo) {
	memset(quadrantInfo, 0, 4*(sizeof(int)));
	if(x >= 0)
		if (y >= 0)  quadrantInfo[0] = 1; else quadrantInfo[3] = 1;
	else
		if (y >= 0)  quadrantInfo[1] = 1; else quadrantInfo[2] = 1;
}

void add(int *q1, int *q2, int *sum) {
	sum[0] = q1[0] + q2[0]; 
	sum[1] = q1[1] + q2[1];
	sum[2] = q1[2] + q2[2]; 
	sum[3] = q1[3] + q2[3];
}

void addTo(int *q1, int *sum) {
	sum[0] += q1[0];
	sum[1] += q1[1];	
	sum[2] += q1[2];
	sum[3] += q1[3];
}

void reflectQX(int *q) {
	swap(&q[0], &q[3]);
	swap(&q[1], &q[2]);
}

void reflectQY(int *q) {
	swap(&q[0], &q[1]);
	swap(&q[3], &q[2]);
}

void printQuadrant(int *q) {
	printf("%d %d %d %d\n", q[0], q[1], q[2], q[3]);
}

int *createQuadrantInfo(int x, int y) {
	int *q = (int*)malloc(4*sizeof(int));
	findQuadrandInfo(x, y, q);
	return q;
}

/* Interval node */
typedef struct _INode 
{
	int low, high, mid; /* intervals inclusive */
	struct _INode *left, *right;
	int *result;
} INode;

typedef struct _ITree
{
	INode *root;
	int **pointInfo; /* quadrant calculation for each point */
	int size;
} ITree;

INode* constructITree(ITree *tree, int low, int high) {
	INode *cur = (INode*)malloc(sizeof(INode));
	cur->low = low; cur->high = high;
	cur->mid = (low+high)/2;
	cur->left = cur->right = 0;
	if(cur->low == cur->high)
		cur->result = tree->pointInfo[cur->low];
	else {
		cur->left = constructITree(tree, cur->low, cur->mid);
		cur->right = constructITree(tree, cur->mid + 1, cur->high);
		cur->result = (int*)malloc(4*sizeof(int));
		add(cur->left->result, cur->right->result, cur->result);
	}
	return cur;
}

ITree* createITree(int **p, int size) {
	ITree *tree = (ITree*)malloc(sizeof(ITree));
	tree->pointInfo = p;
	tree->size = size;
	tree->root = constructITree(tree, 0, size-1);
	return tree;
}

/*	void resetUpdateLowHigh() {
		updateLow = pointData.size();
		updateHigh = -1;
		updated = false;
		}*/
/*
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
*/

void getInfo(INode *cur, int i, int j, int *qInfo) {
	if(!cur) return;
	
	if(cur->low == i && cur->high == j) {
		addTo(cur->result, qInfo);
		return;
	}
	
	if(i > cur->mid) return getInfo(cur->right, i, j, qInfo);
	if(j <= cur->mid) return getInfo(cur->left, i, j, qInfo);
	
	getInfo(cur->right,cur->mid+1, j, qInfo);
	getInfo(cur->left, i, cur->mid, qInfo);
}
void ref(int *q, int XorY) {
	if( XorY )
		reflectQX(q);
	else
		reflectQY(q);
}
void reflect(INode* cur, int i, int j, int XorY) {

	if(!cur) return;
	if(cur->low == cur->high) { 
		ref(cur->result, XorY); return; 
	}

	if(i > cur->mid) reflect(cur->right, i, j, XorY);
	else if(j <= cur->mid) reflect(cur->left, i, j, XorY);
	else {
		reflect(cur->left, i , cur->mid, XorY);
		reflect(cur->right, cur->mid+1, j, XorY);
	}
	add(cur->left->result, cur->right->result, cur->result);
}

void reflectX(ITree *tree, int i, int j) {
	reflect(tree->root, i, j, 1);
}

void reflectY(ITree *tree, int i, int j) {
	reflect(tree->root, i, j, 0);
}


/*
	void ref(int *q) { // quadrant
		if( XorY )
			reflectQX(q);
		else
			reflectQY(q);
			}*/

/*	void fastreflect(int i, int j) {
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
	};*/

void solveQuadrantQueries()
{
	int nPoints;
	scanf("%d", &nPoints);
	int **quadrantData = (int**)malloc(nPoints*sizeof(int*));
	for(int point = 0; point < nPoints; ++point)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		quadrantData[point] = createQuadrantInfo(x, y);
	}
	ITree *intervalTree = createITree(quadrantData, nPoints);
	int nQueries;
	scanf("%d", &nQueries);
	int *q = (int*)malloc(4*sizeof(int));
	
	for(int query = 0; query < nQueries; ++query)
	{
		int i, j;
		char action;
		scanf(" %c %d %d", &action, &i, &j);

		switch (action) {
		case 'C':
			memset(q, 0, 4*sizeof(int));
			getInfo(intervalTree->root, i-1,j-1,q);
			printQuadrant(q);
			break;
		case 'X':
			reflectX(intervalTree, i-1, j-1);
			break;
		case 'Y':
			reflectY(intervalTree, i-1, j-1);
			break;
		}

	}
}

int main(int argc, char *argv[])
{
	solveQuadrantQueries();
	return 0;
}
