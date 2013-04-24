//  What Goes Up 
// 
// Write a program that will select the longest strictly increasing subsequence 
// from a sequence of integers.
// 
// Input
// 
// The input file will contain a sequence of integers (positive, negative, 
// and/or zero). Each line of the input file will contain one integer.
// 
// Output
// 
// The output for this program will be a line indicating the length of the 
// longest subsequence, a newline, a dash character ('-'), a newline, and then 
// the subsequence itself printed with one integer per line. If the input 
// contains more than one longest subsequence, the output file should print 
// the one that occurs last in the input file.
// 
// Notice that the second 8 was not included -- the subsequence must be 
// strictly increasing.
// 
// Sample Input
// 
// -7
// 10
// 9
// 2
// 3
// 8
// 8
// 1
// Sample Output
// 
// 4
// -
// -7
// 2
// 3
// 8

#include <cstdio>
#include <vector>
#include <algorithm>

#define VI vector<int>
using namespace std;

void LIS(VI &vec, VI &lis)
{
	lis.clear();
	if(vec.size() == 0) return;
	VI backtrack(vec.size());
	backtrack[0] = 0;
	int maxindex = 0;
	VI arr; arr.push_back(vec[0]);
	VI arrBT; arrBT.push_back(0);
	for(int i = 1; i < vec.size(); ++i) {
		backtrack[i] = i;
		if(arr[arr.size()-1] < vec[i]) {
			arr.push_back(vec[i]);
			backtrack[i] = arrBT[arrBT.size()-1];
			arrBT.push_back(i);
			maxindex = i;
		}
		else {
			VI::iterator it = lower_bound(arr.begin(), arr.end(), vec[i]);
			*it = vec[i];
			int arrBTIdx = it-arr.begin();
			arrBT[arrBTIdx] = i;
			if( arrBTIdx != 0)
				backtrack[i] = arrBT[arrBTIdx-1];
			if(arrBTIdx == arrBT.size()-1)
				maxindex = i;
		}
	}
	while(backtrack[maxindex] != maxindex) {
		lis.push_back(vec[maxindex]);
		maxindex = backtrack[maxindex];
	}
	lis.push_back(vec[backtrack[maxindex]]);
	reverse(lis.begin(), lis.end());
}

int main(int argc, char *argv[])
{
	int n;
	VI vec;
	while(scanf(" %d", &n) != EOF) {
		vec.push_back(n);
	}
	VI lis;
	LIS(vec,lis);
	printf("%d\n", lis.size());
	printf("-\n");
	for(int i = 0; i < lis.size(); i++)
		printf("%d\n", lis[i]);

	return 0;
}
