#include <cstdio>
#include <cstring>

typedef long long LL;

LL memo[51][51][51];
int origUnits;
LL BC(int nUnits, int kBar, int mUnits)
{
	if(nUnits < 0) return 0;
	if(memo[nUnits][kBar][mUnits] < 0) {
		if(nUnits == 0 || kBar == 0 || mUnits == 0 || nUnits < kBar) 
			memo[nUnits][kBar][mUnits] = 0;
		else if(kBar == 1 && nUnits <= mUnits)
			memo[nUnits][kBar][mUnits] = 1;
		else {
			memo[nUnits][kBar][mUnits] = 0;
			for(int i = 1; i <= mUnits; i++)
				memo[nUnits][kBar][mUnits] += BC(nUnits-i, kBar-1, origUnits);
			//memo[nUnits-1][kBar] = 0;
			//memo[nUnits-1][kBar-1] = 0;
		} 
	}
	return memo[nUnits][kBar][mUnits];
}

int main(int argc, char *argv[])
{
	int nUnits, kBar;
	while(scanf(" %d %d %d", &nUnits, &kBar, &origUnits) != EOF)
	{
		memset(memo, -1, sizeof memo);
		printf("%llu\n", BC(nUnits, kBar, origUnits));
	}
	return 0;
}
