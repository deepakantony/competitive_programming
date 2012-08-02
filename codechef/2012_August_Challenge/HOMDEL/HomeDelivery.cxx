#include <cstdio>
#include <algorithm>
using namespace std;

// Floyd warshall 
int main(int argc, char *argv[]) {
	int N; scanf("%d", &N);
    int T[250][250];
	for(int row = 0; row < N; ++row)
		for(int col = 0; col < N; ++col)
			scanf(" %d", &T[row][col]);
    // find the shortest between each pair.
	for(int k = 0; k < N; ++k)
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < N; ++j)
                T[i][j] = min(T[i][j], T[i][k]+T[k][j]);
    int M; scanf(" %d", &M);
	for(int scenario = 0; scenario < M; ++scenario) {
		int S,G,D;
		scanf(" %d %d %d", &S, &G, &D);
		
        int timeTaken = T[S][G] + T[G][D];
        int timeWasted = max(0, timeTaken-T[S][D]);
		printf("%d %d\n", timeTaken, timeWasted);
	}
	return 0;
}

