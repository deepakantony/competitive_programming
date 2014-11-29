// Substring Diff 
// Given two strings of length n,P = p1...pn  and Q = q1...qn, we define 
// M(i, j, k) as the number of mismatches between pi...pi+k-1 and qj..qj+k-1. 
// That is in set notation, M(i, j, k) refers to the size of the set 
// { 0<=x<k |pi+x not equal to qj+x| }.
// 
// Given an integer K, your task is to find the maximum length L such that 
// there exists pair of indices (i,j) for which we have M(i, j, L) <= K. Of 
// course, we should also have i+L-1 <=n and j+L-1 <=n.
// 
// Input
// First line of input contains a single integer T (1 <=T <=10). T test 
// cases follow.
// Each test case consists of an integer K and two strings P and Q separated 
// by a single space. 
// 
// Output
// For each test case output a single integer L which is the maximum value 
// for which there exists pair of indices (i,j) such that M(i, j, L) <=K.
// 
// Constraints
// 
// 0 <= K <= length of the string P
// Both P & Q would have the same length
// The size of each of the string would be at the max 1500
// All characters in P & Q are lower-case English letters.
// 
// Sample Input
// 
// 3
// 2 tabriz torino
// 0 abacba abcaba
// 3 helloworld yellomarin
// 
// Sample Output
// 
// 4
// 3
// 8 
// 
// Explanation:
// 
// First test-case: If we take "briz" from the first string, and "orin" from 
// the second string, then the number of mismatches between these two 
// substrings is equal to 2, and the length of these substrings are 4. 
// That's we have chosen i=3, j=2, L=4, and we have M(3,2,4) = 2.
// Second test-case: Since K=0, we should find the longest common substring 
// for the given input strings. We can choose "aba" as the result, and we 
// don't have longer common substring between two strings. So, the answer 
// is 3 for this test-case. That's we have chosen i=1, j=4, and L=3, and we 
// have M(1,4,3)=0.
// Third test-case: We can choose "hellowor" from first string and "yellomar" 
// from the second string. So, we have chosen i=1, j=1, and L=8, and we have 
// M(1,1,8)=3. Of course we can also choose i=2, j=2, and L=8 and we still 
// have M(2,2,8)=3.

#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>

using namespace std;
int memo[1501][1501];
char P[1501], Q[1501];
int N, K;

void print(int i, int j, int L)
{
	for(int k = i; k < i+L; k++)
		printf("%c", P[k]);
	printf("\n");
	for(int k = j; k < j+L; k++)
		printf("%c", Q[k]);
	printf("\n");
}

int diff(int pi, int qj, int n)
{
	int res = 0;
	for(int i = 0; i < n; ++i)
		if(P[i+pi] != Q[i+qj])
			res++;
	return res;
}

int getL(int i, int j, int k ) 
{
	int L = 0;
	for(; i < N && j < N && k > 0; i++, j++)
	{
		if(P[i] != Q[j])
			k--;
		++L;
	}
	if(k == 0)
		for(; i < N && j < N && P[i] == Q[j]; i++, j++)
			++L;
	return L;
}

int getNextL(int i, int j, int prevL) 
{
	if(P[i-1] == Q[j-1]) return prevL-1;

	return prevL + getL(i+prevL, j+prevL, 0);
}

int maxL()
{
	if (N == K) return N;
	memset(memo, 0, sizeof memo);
//	printf("%d %d %s %s\n", N, K, P, Q);
	int L = 0;
	for(int i = 0; i < N-L; ++i) {
		if((memo[0][i] = getL(0,i, K)) > L) {
			L = memo[0][i];
//				printf("%d %d %d\n", L, 0 , i);
//			print(0, i, L);
		}
		if((memo[i][0] = getL(i, 0, K)) > L) {
			L = memo[i][0];
//				printf("%d %d %d\n", L, i , 0);
//			print(i, 0, L);
		}
	}
	for(int i = 1; i < N-L; ++i) {
		if((memo[i][i] = getNextL(i, i, memo[i-1][i-1])) > L) {
			L = memo[i][i];
//				printf("%d %d %d\n", L, i , i);
//			print(i, i, L);
		}
		for(int j = i+1; j < N-L; ++j) {
			
			if((memo[i][j] = getNextL(i, j, memo[i-1][j-1])) > L) {
				L =  memo[i][j];
//				printf("%d %d %d\n", L, i , j);
//				print(i, j, L);
			}

			if((memo[j][i] = getNextL(j, i, memo[j-1][i-1])) > L) {
				L = memo[j][i];
//				printf("%d %d %d\n", L, i , j);
//				print(j, i, L);
			}
		}
	}
		
	return L;
}

int main(int argc, char *argv[])
{
	clock_t start = clock();

	int nTests; scanf(" %d", &nTests);
	while(nTests--) {
		scanf(" %d %s %s", &K, P, Q);
		N = strlen(P);
		printf("%d\n", maxL());
	}

	fprintf(stderr, "Time taken: %.3f\n", 
			((double)(clock()-start))/CLOCKS_PER_SEC);
}
