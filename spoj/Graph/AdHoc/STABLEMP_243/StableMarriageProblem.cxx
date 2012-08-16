// Stable marriage problem - using gale shapley algorithm

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> VI;


int main (int argc, char *argv[]) {
	int T; scanf("%d",&T);
	int 
	// Store both men's and women's preference
	
// for every man M, pick his most preferred woman W, he has not yet proposed to
//  if the woman W is not engaged
//      engage with her, mark M and W as engaged
//  if the woman W is engaged and her preference for the man M is higher 
//      engage to man M, mark M as engaged, mark the previous man M' as free
//  remove W from M's preference.
