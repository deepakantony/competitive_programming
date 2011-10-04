#include "NGonRing.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//
// Constructor
NGonRing::NGonRing(int nGon)
	:_nGon(nGon)
{
	_totalDigits = nGon*2;
}


//
// Generate solutions for the total
bool NGonRing::generateSolutions( 
	int totalPerLine, vector<string> &nGonRingSolutions
	) const
{
	vector<int> possibleSolutions;
	for(int entry = 1; entry <= _nGon; entry++)
		possibleSolutions.push_back(entry);

	do
	{
		if (isValidSolution(possibleSolutions))
		{
			nGonRingSolutions.push_back(
				convertVectorToString(possibleSolutions)
				);
		}
	}
	while(
		next_permutation(possibleSolutions.begin(), possibleSolutions.end())
		);
	
	return true;
}

//
// Generate all solutions 
bool NGonRing::generateSolutions( vector<string> &nGonRingSolutions	) const
{
	// The lowest & highest total of the NGonRing
	int lowestTotal = _nGon/2 + (_nGon/2 - 1) + (_nGon/2 + 1);
	int highestTotal = lowestTotal + 2;

	for (int total = lowestTotal; total <= highestTotal; total++)
	{
		generateSolutions(total, nGonRingSolutions);
	}

	return true;
}

//
// is the solution a valid solution
bool NGonRing::isValidSolution( const vector<int> &solution ) const
{
	if(solution.size() > _nGon*3)
		return false;

	return true;
}

//
// Convert the vector of integers to string
string convertVectorToString(const std::vector<int> &solutionVector)
{
	string res;
	for(vector<int>::const_iterator it = solutionVector.begin();
		it != solutionVector.end(); it++)
		res += int2String(*it);
	return res;
}

// 
// Convert int to string
string int2String(int n)
{
	string res;
	while(n>0)
	{
		res += ('0' + n%10);
		n /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}


// 
// Our special display function
bool displaySolutions (
	int nGon, int totalPerLine, const vector<string> &nGonRingSolutions
	)
{
	return true;
}

