#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned long long LL;
LL memo[10][1001];
int wind[10][1001];

LL totalGasRequired(int altitude, int distance)
{
	if(memo[altitude][distance] == -1) {
		if(altitude == 0 && distance == 0)
			memo[altitude][distance] = 0;
		else if(altitude > distance)
			memo[altitude][distance] = -200;
		else {
			memo[altitude][distance] = 30 - wind[altitude][distance] +
				totalGasRequired(altitude, distance-1);
			if(altitude < 9)
				memo[altitude][distance] = min(memo[altitude][distance],
											   60llu - wind[altitude][distance] +
											   totalGasRequired(altitude+1, 
																distance-1));
			if(altitude > 0)
				memo[altitude][distance] = min(memo[altitude][distance],
											   20llu - wind[altitude][distance] +
											   totalGasRequired(altitude-1, 
																distance-1));
		}
	}
	return memo[altitude][distance];
}

int main(int argc, char *argv[])
{
	
	int nTests;
	scanf("%d", &nTests);
	int X;
	memset(wind, 0, sizeof wind);
	while(nTests--) {
		scanf(" %d", &X);
		X = X/100;
		
		for(int altitude = 9; altitude >= 0; altitude--) 
			for(int distance = X; distance > 0; distance--)
				scanf(" %d", &wind[altitude][distance]);
		memset(memo, -1, sizeof memo);
		printf("%d\n\n", totalGasRequired(0, X));
	}
	return 0;

}
