#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

inline void swap(int *a, int *b) {
	int temp = *a;
	*a = *b; *b = temp; 
}

inline void findQuadrandInfo(int x, int y, int *quadrantInfo) {
	memset(quadrantInfo, 0, 4*(sizeof(int)));
	if(x >= 0)
		if (y >= 0)  quadrantInfo[0] = 1; else quadrantInfo[3] = 1;
	else
		if (y >= 0)  quadrantInfo[1] = 1; else quadrantInfo[2] = 1;
}

inline void add(int *q1, int *q2, int *sum) {
	sum[0] = q1[0] + q2[0]; 
	sum[1] = q1[1] + q2[1];
	sum[2] = q1[2] + q2[2]; 
	sum[3] = q1[3] + q2[3];
}

inline void addTo(int *q1, int *sum) {
	sum[0] += q1[0];
	sum[1] += q1[1];	
	sum[2] += q1[2];
	sum[3] += q1[3];
}

inline void reflectQX(int *q) {
	swap(&q[0], &q[3]);
	swap(&q[1], &q[2]);
}

inline void reflectQY(int *q) {
	swap(&q[0], &q[1]);
	swap(&q[3], &q[2]);
}

inline void printQuadrant(int *q) {
	printf("%d %d %d %d\n", q[0], q[1], q[2], q[3]);
}

inline int left(int index) {
	return 2*index + 4;
}
inline int right(int index) {
	return 2*index + 4;
}
inline int parent(int index) {
	return (index-4)/2;
}

int curI, curJ, curReflect;
int *tree;
int size;
int *q;

void initialize(int cur, int low, int high) {	
	int l = left(cur), r = right(cur), mid = (low+high)/2;
	if(low+2 == high) {
		if(low == mid)
			initialize(r, mid+1, high);
		else 
			initialize(l, low, mid);
	}
	else if(low+1 != high) { // sum up and return
		initialize(l, low, mid);
		initialize(r, mid+1, high);
	}
	add(tree+l, tree+r, tree+cur);
}

void getInfo(int cur, int low, int high) {
	if(low == high) addTo(tree+cur, q);
	else if(low >= curI && high <= curJ) addTo(tree+cur, q);
	else {
		int l = left(cur), r = right(cur), mid = (low+high)/2;
		if(curI > mid) getInfo(r, mid+1, high);
		else if(curJ <= mid) getInfo(l, low, mid);
		else {
			getInfo(r, mid+1, high);
			getInfo(l, low, mid);
		}
	}
}

void reflectQ(int *q) {
	if(curReflect)
		reflectQX(q);
	else
		reflectQY(q);
}

void swapReflect(int cur, int low, int high) {
	if(low == high) {
		reflectQ(tree+cur);
	}
	else {
		int mid = (low+high)/2;
		swapReflect(left(cur), low, mid);
		swapReflect(right(cur), mid+1, high);
		reflectQ(tree+cur);
	}
}

void reflect(int cur, int low, int high) {
	if(low == high) reflectQ(tree+cur);
	else if(low >= curI && high <= curJ)
		swapReflect(cur, low, high);
	else {
		int l = left(cur), r = right(cur), mid = (low+high)/2;
		if(curI > mid) reflect(r, mid+1, high);
		else if(curJ <= mid) reflect(l, low, mid);
		else {
			reflect(l, low, mid);
			reflect(r, mid+1, high);
		}
		add(tree+l, tree+r, tree+cur);
	}
}

void solveQuadrantQueries()
{
	scanf("%d", &size);
	tree = (int*)malloc(ceil(log2(size))*size*sizeof(int));

	for(int point = 0; point < size; ++point)
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

