// Add All
// Input: standard input
// Output: standard output
// 
// Yup!! The problem name reflects your task; just add a set of numbers. But 
// you may feel yourselves condescended, to write a C/C++ program just to add 
// a set of numbers. Such a problem will simply question your erudition. So, 
// let’s add some flavor of ingenuity to it.
//  
// Addition operation requires cost now, and the cost is the summation of 
// those two to be added. So, to add 1 and 10, you need a cost of 11. If 
// you want to add 1, 2 and 3. There are several ways –
//  
// 1 + 2 = 3, cost = 3
// 3 + 3 = 6, cost = 6
// Total = 9
// 1 + 3 = 4, cost = 4
// 2 + 4 = 6, cost = 6
// Total = 10
// 2 + 3 = 5, cost = 5
// 1 + 5 = 6, cost = 6
// Total = 11
//  
// I hope you have understood already your mission, to add a set of integers 
// so that the cost is minimal.
//  
// Input
// Each test case will start with a positive number, N (2 ≤ N ≤ 5000) 
// followed by N positive integers (all are less than 100000). Input is 
// terminated by a case where the value of N is zero. This case should not 
// be processed.
//  
// Output
// For each case print the minimum total cost of addition in a single line.
//  
// Sample Input                           Output for Sample Input
// 3
// 1 2 3
// 4
// 1 2 3 4
// 0
//  
// 9
// 19
//
// Problem setter: Md. Kamruzzaman, EPS

#include <cstdio>
#include <queue>
#include <functional>

#define REP(i, n) for(int (i) = 0; (i) < (n); ++(i))

using namespace std;
typedef unsigned long long ull;

int main(int argc, char *argv[])
{
	
	int size, n;
	ull cost, sum;
	priority_queue<ull, vector<ull>, greater<int> > pq;
	scanf(" %d", &size);
	while(size > 1) {
		REP(i, size) {
			scanf(" %d", &n);
			pq.push(n);
		}
		cost = 0;
		while(pq.size() > 1) {
			sum = pq.top();
			pq.pop();
			sum += pq.top();
			pq.pop();
			cost += sum;
			pq.push(sum);
		}
		pq.pop();
		printf("%llu\n", cost);
		scanf(" %d", &size);
	}

	return 0;
}
