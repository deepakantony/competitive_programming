// Problem A: Trainsorting
// 
// Erin is an engineer. She drives trains. She also arranges the cars within 
// each train. She prefers to put the cars in decreasing order of weight, 
// with the heaviest car at the front of the train.
// Unfortunately, sorting train cars is not easy. One cannot simply pick up a 
// car and place it somewhere else. It is impractical to insert a car within 
// an existing train. A car may only be added to the beginning and end of the 
// train.
// 
// Cars arrive at the train station in a predetermined order. When each car 
// arrives, Erin can add it to the beginning or end of her train, or refuse 
// to add it at all. The resulting train should be as long as possible, but 
// the cars within it must be ordered by weight.
// 
// Given the weights of the cars in the order in which they arrive, what is 
// the longest train that Erin can make?
// 
// Input Specification
// 
// The first line is the number of test cases to follow. The test cases 
// follow, one after another; the format of each test case is the following:
// The first line contains an integer 0 <= n <= 2000, the number of cars. 
// Each of the following n lines contains a non-negative integer giving the 
// weight of a car. No two cars have the same weight.
// 
// Sample Input
// 
// 1
// 3
// 1
// 2
// 3
// Output Specification
// 
// Output a single integer giving the number of cars in the longest train 
// that can be made with the given restrictions.
// Output for Sample Input
// 
// 3


#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

int trainCars[2010];
int tempSeq[2010];
int LISSeq[2010];
int LDSSeq[2010];

int LDS(int size) {
	if(size == 0) return 0;
	int lds = 1;
	tempSeq[0] = trainCars[0];
	LDSSeq[0] = 0;
	REP(i, 1, size) {
		int *it = upper_bound(tempSeq, tempSeq+lds, trainCars[i], greater<int>());
		LDSSeq[i] = (int)(it-tempSeq)+1;
		lds = max(lds, (int)(it-tempSeq)+1);
		*it = trainCars[i];
	}
	return lds;
}
int LIS(int size) {
	if(size == 0) return 0;
	int lis = 1;
	tempSeq[0] = trainCars[0];
	LISSeq[0] = 0;
	REP(i, 1, size) {
		int *it = lower_bound(tempSeq, tempSeq+lis, trainCars[i]);
		LISSeq[i] = (int)(it-tempSeq)+1;
		lis = max(lis, (int)(it-tempSeq)+1);
		*it = trainCars[i];
	}
	return lis;
}

int main(int argc, int *argv[])
{
	int nTests; scanf(" %d", &nTests);
	int seqLen;

	while(nTests--) {
		scanf(" %d", &seqLen);
		if(seqLen == 0) { printf("0\n"); continue; }
		REP(i, 0, seqLen) 
			scanf(" %d", &trainCars[seqLen-i-1]);
		LDS(seqLen);
		LIS(seqLen);
		int res = 1;
		REP(i, 0, seqLen)
			res = max(res, LDSSeq[i]+LISSeq[i]-1);

		printf("%d\n", res);
	}
	return 0;
}
