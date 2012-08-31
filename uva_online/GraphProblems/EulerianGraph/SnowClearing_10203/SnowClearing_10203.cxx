// http://uva.onlinejudge.org/external/102/10203.html

#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

typedef long long LL;

// this is simple; since all roads have lanes running both ways, this will form
// a eulerian path. So it's always possible to cover all roads with only 20km/hr
// Because of this just sum up the distances and find the time :)
int main(int argc, char *argv[])
{
	char inp[100];
	int T; cin.getline(inp, 100); 
	assert(sscanf(inp, "%d", &T) == 1);
	LL x, y;
	float a,b,c,d, dist;
	float speed = 20000.f/60.f;
	cin.getline(inp, 100);
	assert(inp[0] == '\0');

	while(T--) {
		dist = 0.f;
		//assert(scanf("%lld%lld", &x, &y) == 2);
		cin.getline(inp, 100);
		assert(sscanf(inp, "%lld %lld", &x, &y) == 2);
		
		while(cin.getline(inp, 100) && cin.good() && inp[0]) {
			assert(sscanf(inp, "%f %f %f %f", &a, &b, &c, &d) == 4);
			dist += 2*sqrt( (a-c)*(a-c) + (b-d)*(b-d) );
		}

		LL time = (LL)(dist/speed + 0.5);
		printf("%lld:%02lld\n", time/60, time%60);
		if(T) printf("\n");
	}
	return 0;
}

