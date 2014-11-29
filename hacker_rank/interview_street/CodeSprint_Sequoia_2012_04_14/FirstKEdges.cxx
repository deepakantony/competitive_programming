#include <cstdio>

#define REP(i, st, n)  for(int (i) = (st); (i) < (n); ++(i))
#define RREP(i, st, n) for(int (i) = (st); (i) >= (n); --(i))

int x[100000];
int y[100000];
int nDisjoint[100000];
int N, M;

class FindUnion {
public:
	FindUnion(int size) : size(size) {
		REP(i, 0, size)
			parent[i] = i;
		nDisjoint = size;
	}
	void unionSet(int i, int j) {
		if(findSet(j) != findSet(i)) {
			nDisjoint--;
			parent[findSet(j)] = findSet(i);
		}
	}
	int findSet(int i) {
		return i == parent[i] ? i : (parent[i] = findSet(parent[i]));
	}
	int numberOfDisjoint() {
		return nDisjoint;
	}
private:
	int parent[10000];
	int nDisjoint;
	int size;
};
	
int main(int argc, char *argv[]) 
{
	scanf(" %d %d", &N, &M);
	REP(edge, 0, M)
		scanf(" %d %d", &x[edge], &y[edge]);
	FindUnion s(N);
	RREP(edge, M-1, 0)
	{
		nDisjoint[edge] = s.numberOfDisjoint();
		s.unionSet(x[edge], y[edge]);
	}

	REP(edge, 0, M)
		printf("%d\n", nDisjoint[edge]);
	return 0;
}
