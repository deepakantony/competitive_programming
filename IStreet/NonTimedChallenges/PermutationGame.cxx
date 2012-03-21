// Permutation Game : Problem description
// 
// Alice and Bob play the following game:
// 
// 1) They choose a permutation of the first N numbers to begin with.
// 2) They play alternately and Alice plays first.
// 3) In a turn, they can remove any one remaining number from the permutation.
// 4) The game ends when the remaining numbers form an increasing sequence. 
// The person who played the last turn (after which the sequence becomes 
// increasing) wins the game.
// 
// Assuming both play optimally, who wins the game?
// 
// Input:
// The first line contains the number of test cases T. T test cases follow. 
// Each case contains an integer N on the first line, followed by a 
// permutation of the integers 1..N on the second line.
// 
// Output:
// Output T lines, one for each test case, containing "Alice" if Alice wins 
// the game and "Bob" otherwise.
// 
// Constraints:
// 1 <= T <= 100
// 2 <= N <= 15
// The permutation will not be an increasing sequence initially.
// 
// Sample Input:
// 2
// 3
// 1 3 2
// 5
// 5 3 2 1 4
// 
// Sample Output:
// Alice
// Bob
// 
// 
// Explanation: For the first example, Alice can remove the 3 or the 2 to 
// make the sequence increasing and wins the game.
// 

// Use the sprague-grundy theorem. Read up on impartial games, mex rule
// etc...


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int getMex(unordered_set<int> gValSet)
{
	int mex = 0;
	while(true)
	{
		if(gValSet.find(mex) == gValSet.end())
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

int getGrundyIndex(int currentIndex, int removeNum)
{
	return currentIndex | (1 << (removeNum-1));
}

int spragueGrundy(
	const vector<int> &permutation, 
	int grundyFunctionIndex, // sum of the permutation
	unordered_map<int, int> &grundyVals
	)
{
	if(permutation.size() == 2)
	{
		if(permutation[0] < permutation[1])
		{
			grundyVals[grundyFunctionIndex] = 0;
			return 0;
		}
		else
		{
			grundyVals[grundyFunctionIndex] = 1;
			return 1;
		}
	}
			
	if(permutation.size() == 1 || 
	   sorted(permutation.begin(), permutation.end()))
	{
		grundyVals[grundyFunctionIndex]  = 0;
		return 0;
	}
//	printVec (permutation);
//	cout << grundyFunctionIndex << endl;

	int gVal = -1;
	int index = 0;
	unordered_set<int> myGrundyVals;
	for(auto num : permutation)
	{
		int newGrundyIndex = getGrundyIndex(grundyFunctionIndex, num);
		if(grundyVals.find(newGrundyIndex) == grundyVals.end() )
		{
			vector<int> nextPerm;
			int sum = grundyFunctionIndex - num;
			copy(permutation.begin(), permutation.begin() + index, 
				 back_inserter(nextPerm));
			copy(permutation.begin()+index+1, permutation.end(), 
				 back_inserter(nextPerm));
			spragueGrundy(nextPerm, newGrundyIndex, grundyVals);
		}
		myGrundyVals.insert(grundyVals[newGrundyIndex]);
		index++;	
	}
	grundyVals[grundyFunctionIndex] = gVal = getMex(myGrundyVals);
	return gVal;
}

int permutationGame(istream &instream)
{
//	ifstream instream;
//	instream.open(argv[1], ifstream::in);

	int nTests;
	instream >> nTests;

	for(int test = 0; test < nTests; ++test)
	{
		int N;
		instream >> N;
		vector<int> permutation(N);

		for(int index = 0; index < N; ++index)
		{
			int val;
			instream >> val;
			permutation[index] = val;
		}
		// output the winner

		unordered_map<int,int> grundyVals;
		if(spragueGrundy(permutation, 1<<N, grundyVals) == 0)
			cout << "Bob" << endl;
		else
			cout << "Alice" << endl;

		permutation.clear();
		grundyVals.clear();
	}
	return 0;
}

int main(int argc, char *argv[])
{
	return permutationGame(cin);
}
