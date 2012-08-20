#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

int m, n;
int a[20], b[20], c[20];
int visited[10];
int dist[10];

// based on "visited" and "dist" array; determines if the "pos" can be placed
bool canPlace(int pos) {

}

// This backtrack function returns total possible seating arrangements
int totalPossible(int curPossible, int curLen) {
	
}


int main(int argc, char *argv[])
{
	while(scanf("%d %d", &n, &m) != EOF && n != 0) 
	{
		
	}

	return 0;
}

// Problem A: Social Constraints
// 
// 
// Socializing can be a very complicated thing among teenagers. For example, 
// finding a good seating arrangement in a movie theater can be a difficult 
// task. Here is a list of constraints that could potentially apply to two 
// individuals A and B in this situation:
// 
// if A and B are dating, then they must sit beside each other
// if A and B are fighting, then they cannot sit beside each other
// if A and B have just broke up, then they must sit at opposite ends of the row
// Teenage politics is a complicated thing meaning the constraints can get even 
// more complicated than those listed above. However, we restrict this problem 
// to a particular form of constraint that simply specifies a lower or upper 
// bound on the number of seats separating two specific individuals.
// 
// The group arrives after everyone else watching the show has been seated. By 
// some stroke of luck, there are exactly as many open seats as there are 
// teenagers and all of these seats appear consecutively in the front row. How 
// many possible seating arrangements satisfy the constraints?
// 
// Input Format
// 
// Each test case begins with two integers n and m with 0 < n ≤ 8 and 0 ≤ m ≤ 20 
// where n is the size of the group. For simplicity, assume the teenagers are 
// numbered from 0 to n-1. Then of m lines follow, each describing a constraint, 
// where a line consists of three integers a,b,c satisfying 0 ≤ a < b < n and 
// 0 < |c| < n. If c is positive then teenagers a and b must sit at most c seats 
// apart. If c is negative, then a and b must sit at least -c seats apart. The 
// end of input is signaled by a line consisting of n = m = 0.
// 
// Output Format
// 
// The output for each test case is a single line containing the number of 
// possible seating arrangements for the group that satisfy all of the social 
// constraints.
// 
// Sample Input
// 
// 3 1
// 0 1 -2
// 3 0
// 0 0
// Sample Output
// 
// 2
// 6
// Zachary Friggstad
