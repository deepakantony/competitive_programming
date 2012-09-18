#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

uint cyclelength[1000001];

uint calculateCycleLength(uint n) {
	if(n > 1000000) {
		if(n%2 == 0) return 1+calculateCycleLength(n>>1);
		else return 1+calculateCycleLength(3*n+1);
	}
	else {
		if(cyclelength[n] != -1) return cyclelength[n];
		else if(n%2 == 0) return cyclelength[n] = 1+calculateCycleLength(n>>1);
		else return cyclelength[n] = 1+calculateCycleLength(3*n+1);
	}
}

uint getMax(uint low, uint high) {
	if(low > high) swap(low, high);
	uint maxcl = calculateCycleLength(high);
	for(uint i = low; i < high; ++i) {
		maxcl = max(calculateCycleLength(i), maxcl);
	}
	return maxcl;
}

int main(int argc, char *argv[])
{
	uint low, high;
	memset(cyclelength, -1, sizeof cyclelength);
	cyclelength[0] = 0; cyclelength[1] = 1;

	while(scanf(" %d %d", &low, &high) != EOF) {
		printf("%d %d %d\n", low, high, getMax(low, high));
	}

	return 0;
}
