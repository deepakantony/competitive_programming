#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

// Classified as tree but is easily solved with a bit of math :)
int main(int argc, char *argv[]) {
	int T; scanf("%d", &T);
	int N, A, B, total, N1, dups;
	while(T--) {
		scanf("%d%d%d", &N, &A, &B);
		N1 = N - int(log(max(A, B))/log(2)); // readjusted
		total = (1 << N) - 1; // total
		dups = (1<<N1) - 2; // duplicates
		printf("%d\n", total-dups);
	}
	return 0;
}
