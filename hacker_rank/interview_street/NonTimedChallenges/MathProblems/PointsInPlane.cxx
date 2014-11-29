#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;

#define PII pair<int, int>

int memo[1<<17][2];

struct Point { 
Point(int x, int y) : x(x), y(y) {}
int x; int y; 
};

PII minWays(const vector<Point> &pts, int bitmask)
{
	if(memo[bitmask][0] != -1) 
		return make_pair(memo[bitmask][0], memo[bitmask][1]);

	

}



int main(int argc, char *argv[])
{
	int nTests; scanf(" %d", &nTests);
	while(nTests) {
		int N; scanf(" %d", &N);
		vector<Point> pts;
		while(N--) {
			int x,y; scanf(" %d %d", &x, &y);
			pts.push_back(Point(x,y));
		}
		PII res = minWays(pts, 0);
		printf("%d %d\n", res.first, res.second);
	}

	return 0;
}
