// Stacking pancakes 

// Needs a DP; simple 2^(N-1) does not work

#include <cstdio>

int moduloPow(int base, int exponent, int modulo)
{ // from bruce schneier
	int c = 1;
	while(exponent>0) {
		if(exponent & 1)
			c = (c*base)%modulo;
		exponent = exponent >> 1;
		base = (base*base)%modulo;
	}
	return c;
}

int main(int argc, char *argv[])
{
	int nTests; scanf(" %d", &nTests);
	int N;
	while(nTests--) {
		scanf(" %d", &N);
		printf("%d\n",moduloPow(2, N-1, 1000000007));
	}
	return 0;
}
