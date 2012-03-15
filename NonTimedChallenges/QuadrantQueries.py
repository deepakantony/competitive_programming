import sys

def findQuadrandInfo(x, y, quadrantInfo):
    if x >= 0:
        quadrantInfo[0] = 1 if y >= 0 else quadrantInfo[3] = 1
    else:
         quadrantInfo[1] = 1 if y >= 0 else quadrantInfo[2] = 1

def add(q1, q2, sum):
    sum[0] = q1[0] + q2[0]
    sum[1] = q1[1] + q2[1]
    sum[2] = q1[2] + q2[2] 
    sum[3] = q1[3] + q2[3]

def addTo(q1, sum):
    sum[0] += q1[0]
    sum[1] += q1[1]
    sum[2] += q1[2]
    sum[3] += q1[3]

def reflectQX(q):
    q[0], q[3] = q[3], q[0]
    q[1], q[2] = q[2], q[1]

def reflectQY(q):
    q[0], q[1] = q[1], q[0]
    q[3], q[2] = q[2], q[3]

def printQuadrant(q):
    print "%d %d %d %d\n" % q[0], q[1], q[2], q[3]

def left(index):
    return 2*index + 4;

def right(int index):
    return 2*index + 8;

def parent(int index):
    return (index-4)/2;


class Tree:
    def __init__(self, size):
        self.curI = self.curJ = self.curReflect = 0
        self.tree = 
    curI, curJ, curReflect;
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

def main():
    solveQuadrantQueries();

if __name__ == "__main__":
    main()
