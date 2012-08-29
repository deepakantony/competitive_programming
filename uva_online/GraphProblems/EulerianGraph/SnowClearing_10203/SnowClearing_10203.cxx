#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

typedef long long LL;
int main(int argc, char *argv[])
{
	int T; scanf("%d",&T);
	LL x, y;
	float a,b,c,d;
	char inp[100];
	while(T--) {

		scanf("%lld%lld", &x, &y);
		while(cin.getline(inp, 100) && cin.good() && inp[0])
			sscanf(inp, "%f%f%f%f", &a, &b, &c, &d);

	}
	return 0;
}

