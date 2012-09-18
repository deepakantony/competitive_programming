#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <functional>

using namespace std;

#define TRI pair<int, pair<int, int> >
#define MakeTRI(i, j, k) make_pair((i), make_pair((j), (k)))

void isBiggerSmarter(
	const vector< TRI > &triplets,
	vector<int> &finalRes)
{
	if(triplets.size() == 0) return;
	int backtrack[1000], maxIndex, arrBT[1000];
	vector< TRI > arr;
	arr.push_back(triplets[0]);
	maxIndex = backtrack[0] = 0;
	for(int i = 1; i < triplets.size(); ++i) {
		if(arr[arr.size()-1] > triplets[i]) {
			backtrack[i] = arrBT[arr.size()-1];
			arrBT[arr.size()] = i;
			arr.push_back(triplets[i]);
			maxIndex = i;
		}
		else {
			backtrack[i] = i;
			vector<TRI>::iterator it = upper_bound(
				arr.begin(), arr.end(), triplets[i], greater< TRI >());
			int diffIndex = it - arr.begin();
			arr[diffIndex] = triplets[i];
			arrBT[diffIndex] = i;
			if(diffIndex != 0)
				backtrack[i] = arrBT[diffIndex-1];
			if(diffIndex == arr.size()-1)
				maxIndex = i;

		}
	}
	while(backtrack[maxIndex] != maxIndex) {
		finalRes.push_back(triplets[maxIndex].second.second);
		maxIndex = backtrack[maxIndex];
	}
	finalRes.push_back(triplets[maxIndex].second.second);
	reverse(finalRes.begin(), finalRes.end());
}

int main(int argc, char *argv[])
{
	int W, S;
	vector< TRI > triplets;
	int index = 1;
	while(scanf(" %d %d", &W, &S) != EOF) 
		triplets.push_back(MakeTRI(W, S, index++));
	sort(triplets.begin(), triplets.end());
	vector<int> finalRes;
	for(int i = 0; i < triplets.size(); i++)
	{ int temp = triplets[i].first; 
		triplets[i].first = triplets[i].second.first;
		triplets[i].second.first = temp;
	}

	isBiggerSmarter(triplets, finalRes);


	printf("%d\n", (int)finalRes.size());
	for(int i = 0; i < finalRes.size(); i++)
		printf("%d\n", finalRes[i]);
	return 0;
}
