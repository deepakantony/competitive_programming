#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int getMex(vector<int>::const_iterator begin, 
		   vector<int>::const_iterator end)
{
	int mex = 0;
	while(true)
	{
		if(find(begin, end, mex) == end)
			return mex;
		else
			++mex;
	}
}

typedef vector<int>::const_iterator iter;
bool sorted(iter begin, iter end)
{
	for(iter cur = begin+1, prev = begin;
		cur != end; ++cur, ++prev)
		if(*cur < *prev)
			return false;
	return true;
}

void printVec(vector<int> v)
{
	cout << "( ";
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, ","));
	cout << " )" << endl;
}

int spragueGrundy(
	const vector<int> &permutation, 
	int grundyFunctionIndex, // sum of the permutation
	vector<int> &grundyVals
	)
{
	cout << permutation.size() << endl;
	int temp;
	cin >> temp;
	if(sorted(permutation.begin(), permutation.end()))
	{
		grundyVals[grundyFunctionIndex]  = 0;
		return 0;
	}
	printVec (permutation);
	cin >> temp;

	int gVal = -1;
	int index = 0;
	vector<int> myGrundyVals(permutation.size());
	for(auto it = permutation.begin(); it != permutation.end(); ++it)
	{
		int num = *it;
		if(grundyVals[grundyFunctionIndex-num] == -1)
		{
			vector<int> nextPerm(permutation.size()-1);
			int sum = grundyFunctionIndex - num;
			copy(permutation.begin(), permutation.begin() + index - 1, 
				 back_inserter(nextPerm));
			copy(permutation.begin()+index+1, permutation.end(), 
				 back_inserter(nextPerm));
			spragueGrundy(nextPerm, grundyFunctionIndex-num, grundyVals);
		}
		myGrundyVals.push_back(grundyVals[grundyFunctionIndex-num]);
		index++;	
	}
	grundyVals[grundyFunctionIndex] = gVal = 
		getMex(myGrundyVals.begin(), myGrundyVals.end());
	return gVal;
}

int main(int argc, char *argv[])
{
	int nTests;
	cin >> nTests;

	for(int test = 0; test < nTests; ++test)
	{
		int N;
		cin >> N;
		vector<int> permutation(N, 0);
		for(int index = 0; index < N; ++index)
		{
			int val;
			cin >> val;
			permutation.push_back(val);
		}
		cout << N << endl;
		// output the winner
		int sumNTerms = N*(N+1)/2;
		vector<int> grundyVals(sumNTerms+1, -1);
		if(spragueGrundy(permutation, sumNTerms, grundyVals) == 0)
			cout << "Bob" << endl;
		else
			cout << "Alice" << endl;
	}
	return 0;
}

