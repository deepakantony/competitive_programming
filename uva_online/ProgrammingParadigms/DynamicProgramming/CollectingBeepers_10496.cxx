// Problem E
// Collecting Beepers
// Input: standard input
// Output: standard output
// Time Limit: 2 seconds
// 
// Karel is a robot who lives in a rectangular coordinate system where each 
// place is designated by a set of integer coordinates (x and y). Your job 
// is to design a program that will help Karel pick up a number of beepers 
// that are placed in her world. To do so you must direct Karel to the 
// position where each beeper is located. Your job is to write a computer 
// program that finds the length of the shortest path that will get Karel 
// from her starting position, to each of the beepers, and return back again 
// to the starting position.
//  
// Karel can only move along the x and y axis, never diagonally. Moving from 
// one position (i, j) to an adjacent position (i, j + 11), (i, j-1 ), 
// (i-1, j), or (i+1, j), j) has a cost of one.
//  
// You can assume that Karel’s world is never larger than 20 x _ 20 squares 
// and that there will never be more than 10 beepers to pick up. Each 
// coordinate will be given as a pair (x, y) ) where each value will be in 
// the range 1 through the size of that particular direction of the 
// coordinate system.
//  
// Input
// First there will be a line containing the number of scenarios you are 
// asked to help Karel in. For each scenario there will first be a line 
// containing the size of the world. This will be given as two integers 
// (x-size and y-size). Next there will be one line containing two numbers 
// giving the starting position of Karel. On the next line there will be 
// one number giving the number of beepers. For each beeper there will be 
// a line containing two numbers giving the coordinates of each beeper.
// Output
// 
// The output will be one line per scenario, giving the minimum distance 
// that Karel has to move to get from her starting position to each of the 
// beepers and back again to the starting position.
// Sample Input
// 
// 1
// 10 10
// 1 1
// 4
// 2 3
// 5 5
// 9 4
// 6 5
// Sample Output
// 
// The shortest path has length 24
// A Swedish Problem

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cmath>
#include <ctime>
#include <climits>

using namespace std;

#define PII pair<int, int>

int memo[11][1<<12];
PII locs[11]; 
int N;

int dist(int i, int j) {
	return abs(locs[i].first-locs[j].first) +
		abs(locs[i].second-locs[j].second);
}

int minPath(int curloc, int mask) 
{
	if(mask == (1<<N)-1) return dist(curloc, 0);
	if(memo[curloc][mask] != -1) return memo[curloc][mask];
	int res = 2000000000;
	for(int i = 1; i <= N; ++i)
		if(!(mask & (1<<(i-1))))
		   res = min(res, dist(curloc, i) + minPath(i, mask | (1<<(i-1))));
	return memo[curloc][mask] = res;
}

int main(int argc, char *argv[])
{
	clock_t start = clock();
	int nTests;
	scanf(" %d", &nTests);
	for(int test = 0; test < nTests; ++test) {
		int xsize, ysize; scanf(" %d %d", &xsize, &ysize);
		int x,y;
		scanf(" %d %d", &locs[0].first, &locs[0].second);
		scanf(" %d", &N);
		for(int beeper = 1; beeper <= N; ++beeper)
			scanf(" %d %d", &locs[beeper].first, &locs[beeper].second);

		memset(memo, -1, sizeof memo);
		printf("The shortest path has length %d\n", minPath(0,0));
	}
	fprintf(stderr, "Time taken: %.3f\n", 
			((double)(clock()-start))/CLOCKS_PER_SEC);
	return 0;
}
