#include "NGonRing.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/foreach.hpp>

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
	vector<int> possibleSolutions, regularPermutation;
	for(int entry = 1; entry <= _nGon*2; entry++)
		regularPermutation.push_back(entry);

	do
	{
		convertPermutationToSolution(regularPermutation, possibleSolutions);

		if ( isValidSolution(possibleSolutions, totalPerLine) )
		{
			nGonRingSolutions.push_back(
				convertVectorToString(possibleSolutions)
				);
		}
	}
	while(
		next_permutation(regularPermutation.begin(), regularPermutation.end())
		);
	
	return true;
}

//
// Generate solutions for the total
bool NGonRing::generateSolutions( 
	int totalPerLine, vector<vector<int> > &nGonRingSolutions
	) const
{
	vector<int> possibleSolutions, regularPermutation;
	for(int entry = 1; entry <= _nGon*2; entry++)
		regularPermutation.push_back(entry);

	do
	{
		convertPermutationToSolution(regularPermutation, possibleSolutions);

		if ( isValidSolution(possibleSolutions, totalPerLine) && 
			 (! isCyclicWithExisting(possibleSolutions, nGonRingSolutions))
			)
		{
			rotateTheSolution( possibleSolutions );
			nGonRingSolutions.push_back( possibleSolutions );
		}
	}
	while(
		next_permutation(regularPermutation.begin(), regularPermutation.end())
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
// Check if the solution already exist
bool NGonRing::isCyclicWithExisting(
	const vector<int> solution, const vector<vector<int> > &nGonRingSolutions
	) const
{
	// invalid cases will return true for being cyclic
	if(solution.size() < 3)
		return true;
	// no solutions yet so no duplicates
	if(nGonRingSolutions.size() <= 0)
		return false;


	BOOST_FOREACH(vector<int> solutionEntry, nGonRingSolutions)
	{
		for(int solIndex = 0; solIndex < solutionEntry.size(); solIndex+=3)
			if(solution[0] == solutionEntry[solIndex] &&
			   solution[1] == solutionEntry[solIndex+1] && 
			   solution[2] == solutionEntry[solIndex+2])
				return true;
	}

	return false;
}

void swap(int *item1, int *item2)
{
	int temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}


//
// three item swap
void threeItemSwap(int *index1, int *index2)
{
	for(int index = 0; index < 3; index++)
		swap(index1+index, index2+index);
}

//
// rotate the solution such that smallest set is in the beginning
void NGonRing::rotateTheSolution(vector<int> &solution) const
{
	// find the smallest set
	int smallestIndex = 0;
	for(int sIndex = 3; sIndex < solution.size(); sIndex+=3)
		if(solution[sIndex] < solution[smallestIndex])
			smallestIndex = sIndex;
	
	// if no shifting is required
	if( smallestIndex == 0 )
		return;

	for(int sIndex = smallestIndex; sIndex < solution.size(); sIndex += 3)
		for(int swapIndex = sIndex - 3; swapIndex >= (smallestIndex - sIndex);
			swapIndex -= 3)
			threeItemSwap(&solution[swapIndex], &solution[sIndex]);

	
}

//
// Convert permutation to solution
bool NGonRing::convertPermutationToSolution(
	const vector<int> &regularPermutation, vector<int> &possibleSolutions
	) const
{
	possibleSolutions.clear();
	if(regularPermutation.size() < 3)
		return false;

	for(int rpIndex = 0; rpIndex < regularPermutation.size(); rpIndex++)
	{
		// special cases - front
		if(rpIndex < 3) 
		{
			possibleSolutions.push_back(regularPermutation[rpIndex]);
			continue;
		}
		possibleSolutions.push_back(regularPermutation[rpIndex]);
		possibleSolutions.push_back(regularPermutation[rpIndex-1]);
		// special cases - last element
		if(rpIndex == (regularPermutation.size()-1))
		{
			possibleSolutions.push_back(regularPermutation[1]);
			continue;
		}
		possibleSolutions.push_back(regularPermutation[rpIndex+1]);
		rpIndex++;
	}

	return true;
}


//
// is the solution a valid solution
bool NGonRing::isValidSolution( 
	const vector<int> &solution , int totalPerLine
	) const
{
	if(solution.size() != _nGon*3 && solution.size() <= 0)
		return false;

	int firstSolution = solution[0]+solution[1]+solution[2];

	if(totalPerLine >= 0 && firstSolution != totalPerLine)
		return false;
	for(int startIndex = 3; startIndex < _nGon*3; startIndex += 3)
		if((solution[startIndex] + 
			solution[startIndex+1] +
			solution[startIndex+2]) != firstSolution)
			return false;

	return true;
}

//
// Convert the vector of integers to string
string convertVectorToString(const std::vector<int> &solutionVector)
{
	string res;

	BOOST_FOREACH(int number, solutionVector)
		res += int2String(number);
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
	cout << "( " << nGon << " Gon , total - " << totalPerLine << " ) - ( " 
		 << endl;
	
	BOOST_FOREACH (const string &solutionString, nGonRingSolutions )
	{
		for(int strIndex = 0; strIndex < solutionString.size(); strIndex++)
			if(strIndex%3 == 0 && strIndex != 0) 
				cout << "; " << solutionString[strIndex];
			else
				cout << " " << solutionString[strIndex];
		cout << endl;
	}
	
	cout << " ) " << endl;
	return true;
}


// 
// Our special display function
bool displaySolutions (
	int nGon, int totalPerLine, const vector<vector<int> > &nGonRingSolutions
	)
{
	cout << "( " << nGon << " Gon , total - " << totalPerLine << " ) - ( " 
		 << endl;
	
	BOOST_FOREACH (const vector<int> &solutionVector, nGonRingSolutions )
	{
		for(int vecIndex = 0; vecIndex < solutionVector.size(); vecIndex++)
			if(vecIndex%3 == 0 && vecIndex != 0) 
				cout << "; " << solutionVector[vecIndex];
			else
				cout << " " << solutionVector[vecIndex];
		cout << endl;
	}
	
	cout << " ) " << endl;
	return true;
}

