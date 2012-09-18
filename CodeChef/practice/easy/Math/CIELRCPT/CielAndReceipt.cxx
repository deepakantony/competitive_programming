// http://www.codechef.com/problems/CIELRCPT/

#include <cstdio>
#include <cstdlib>


int main(int argc, char *argv[])
{
	int T; scanf("%d", &T);
	int p;
	while(T--) {
		scanf("%d", &p);
		int res = 0;
		if(p >= 2048)
			res += p>>11;
		for(int pw2 = 1; pw2 < 2048; pw2 *= 2)
			if( (p & pw2) > 0 ) res++;

		printf("%d\n", res);
	}
	return 0;
}


int methodWithModulus(int p) {
	int res = 0;
	if(p > 2048)
		res += p>>11, p %= 2048;
	for(int pw2 = 1; pw2 <= 2048; pw2 *= 2)
		if( (p & pw2) > 0 ) res++;
	return res;
}

int methodWithoutModulus(int p) {
	int res = 0;
	if(p >= 2048)
		res += p>>11;
	for(int pw2 = 1; pw2 < 2048; pw2 *= 2)
		if( p & pw2 ) res++;
	
	return res;
}

void unitTest() {
	//methodWithoutModulus(2049);
	//exit(-1);
	for(int p = 1; p <= 100000; ++p) {
		int resNM = methodWithoutModulus(p), resM = methodWithModulus(p);
		if( resNM != resM )
			printf("%d - %d, %d\n", p, resNM, resM), exit(-1);
	}
}

