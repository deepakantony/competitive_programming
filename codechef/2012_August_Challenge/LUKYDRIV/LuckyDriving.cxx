#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <iterator>
#include <cassert>

using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

#define MOD 1000000007

// this function handles -ve number
LL modme(LL num) {
	return num < 0 ? num + MOD : num%MOD;
}

VVI digitPartition;
int countDigit[10];
char S[10010];

template<typename T>
void printVec(T &vec) {
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}
	

// for the given string of digits, S, I find the count of each digit in it.
void initCountDigit() {
	memset(countDigit, 0, sizeof countDigit);
	for(int i = 0; S[i]; ++i)
		countDigit[S[i]-'0']++;
}

// Given a partion, this function will find the next partion or return false
// if it couldn't find one. This will create partion with only digits and does
// not change the original sum. This will always create unique partitions not
// created before.
bool nextDigitPartition(const VI &prevDigitPartition, VI &next) {
	printVec(prevDigitPartition);
	next = VI(prevDigitPartition.begin(), prevDigitPartition.end());
	// if the last element is 0, then remove it, that's the next partition
	if(next.back() == 0) {
		next.pop_back();
		return true;
	}

	int indivisableTotal = 0;
	while(next.back() == 1)
		indivisableTotal++, next.pop_back();

	
	// At the end, if the length is not 4, add 0's :)
	if(next.size() < 4)
		next.push_back(0);

	assert(next.size() == 4);
	return true;
}

// Generates all paritions that recursively sum to 9 and are atmost 4 digits.
void generateDigitPartitions() {
	int firstDigitPartitions[4][4] = {
		{9, 0, 0, 0},
		{9, 9, 0, 0},
		{9, 9, 9, 0},
		{9, 9, 9, 9}
	};
	REP(i, 4) {
		digitPartition.push_back(VI(firstDigitPartitions[i], 
									firstDigitPartitions[i]+4));
		VI np;
		while(nextDigitPartition(digitPartition.back(), np)) {
			digitPartition.push_back(np);
			np.clear();
		}
	}
}

// return nCr
LL nCr(int n, int r) {
	LL res = 0;
	if(r == 1) res = n;
	else if(r == 2 && n > 1) res = modme(n*(n-1)/2);
	else if(r == 3 && n > 2) res = modme(modme(n*(n-1)/2)*(n-2)/3);
	else if(r == 4 && n > 3) res = modme(modme(modme(n*(n-1)/2)*(n-2)/3)*(n-3)/4);
	return res;
}

// For a given string of digits, S, and count of digits, countDigit, and 
// partition, p, this function will calculate the total ways we generate this
// combination of digit partition.
LL totalWays(const VI &p) {
	int digits[4];
	int c[4] = {0, 0, 0, 0};
	int prev = p[0];
	digits[0] = prev;
	c[0] = 1;
	int curIdx = 0;
	FOR(i, 1, p.size()) {
		if(prev!=p[i]) 
			curIdx++;
		digits[curIdx] = p[i];
		c[curIdx]++;
		prev = p[i];
	}
	LL res = 0;
	curIdx++;
	REP(i, curIdx)
		res = modme(res * nCr(countDigit[digits[i]], c[i]));
		
	printVec(p);
	cout << res << endl;
	return res;
}

// Returns total ways to generate all partition for each input string.
LL getTotalWays() {
	LL res = 0;
	REP(i, digitPartition.size())
		res = modme(res + totalWays(digitPartition[i]));
	return res;
}

int main(int argc, char *arv[]) {
	int T; scanf("%d", &T);
	generateDigitPartitions();
	while(T--) {
		scanf("%s", S);
		initCountDigit();
		
		printf("%lld\n", getTotalWays());
	}
	return 0;
}
