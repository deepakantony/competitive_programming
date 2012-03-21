#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 void swap(int *a, int *b) {
	int temp = *a;
	*a = *b; *b = temp; 
}
void findQuadrandInfo(int x, int y, int *quadrantInfo) {
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
int left(int index) {
	return 2*index + 4;
}
int right(int index) {
	return 2*index + 8;
}
int parent(int index) {
	return (index-4)/2;
}
int curI, curJ, curReflect;
int *tree;
int size;
int *q;

void initialize(int cur, int low, int high) {
	if(low == high) {
		int x, y;
		scanf("%d %d", &x, &y);
		findQuadrandInfo(x, y, tree+cur);
	}
	else {
		int l = left(cur), r = right(cur), mid = (low+high)/2;
		initialize(l, low, mid);
		initialize(r, mid+1, high);

		add(tree+l, tree+r, tree+cur);
	}
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

void printTree() {
	for(int i = 0; i < size; i+=4) {
		printf("i:%d - ", i);
		printQuadrant(tree+i);
	}
}

void solveQuadrantQueries()
{
	int nPoints;
	scanf("%d", &nPoints);
	size = ceil(log2(nPoints))*nPoints*4;

	tree = (int*)malloc(size*sizeof(int));
	memset(tree, 0, size*sizeof(int));
	initialize(0, 0, nPoints-1);

	int nQueries;
	scanf("%d", &nQueries);
	q = (int*)malloc(4*sizeof(int));
	
	for(int query = 0; query < nQueries; ++query)
	{
		char action;
		scanf(" %c %d %d", &action, &curI, &curJ);
		curI--; curJ--;
		switch (action) {
		case 'C':
			memset(q, 0, 4*sizeof(int));
			getInfo(0, 0, nPoints-1);
			printQuadrant(q);
			break;
		case 'X':
			curReflect = 1;
			reflect(0, 0, nPoints-1);
			break;
		case 'Y':
			curReflect = 0;
			reflect(0, 0, nPoints-1);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	solveQuadrantQueries();
	return 0;
}

