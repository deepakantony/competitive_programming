// Easy Problem from Rujia Liu?
// 
// Though Rujia Liu usually sets hard problems for contests (for example, 
// regional contests like Xi'an 2006, Beijing 2007 and Wuhan 2009, or UVa OJ 
// contests like Rujia Liu's Presents 1 and 2), he occasionally sets easy 
// problem (for example, 'the Coco-Cola Store' in UVa OJ), to encourage more 
// people to solve his problems :D
// 
// Given an array, your task is to find the k-th occurrence (from left to 
// right) of an integer v. To make the problem more difficult (and 
// interesting!), you'll have to answer m such queries.
// 
// Input
// 
// There are several test cases. The first line of each test case contains 
// two integers n, m(1<=n,m<=100,000), the number of elements in the array, 
// and the number of queries. The next line contains n positive integers not 
// larger than 1,000,000. Each of the following m lines contains two integer 
// k and v (1<=k<=n, 1<=v<=1,000,000). The input is terminated by end-of-file 
// (EOF). The size of input file does not exceed 5MB.
// 
// Output
// 
// For each query, print the 1-based location of the occurrence. If there is 
// no such element, output 0 instead.
// 
// Sample Input
// 
// 8 4
// 1 3 2 2 4 3 2 1
// 1 3
// 2 4
// 3 2
// 4 2
// Output for the Sample Input
// 
// 2
// 0
// 7
// 0
// 

#include <cstdio>
#include <vector>

#define REP(i, n) for(int (i) = 0; (i) < (n); ++i)

using namespace std;

int main(int argc, char *argv[])
{
	int listSize, nQueries;


	while(scanf(" %d %d", &listSize, &nQueries) != EOF)
	{
		vector<vector<int> > list(1000010);
		REP(i, listSize) {
			int n; scanf(" %d", &n);
			list[n].push_back(i+1);

		}

		REP(i, nQueries) {
			int k, v; scanf(" %d %d", &k, &v);

			if(list[v].size() < k)
				printf("0\n");
			else printf("%d\n", list[v][k-1]);
		}
	}

	return 0;
}
