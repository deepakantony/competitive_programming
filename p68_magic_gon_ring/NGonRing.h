#ifndef _NGONRING_H_
#define _NGONRING_H_

#include <iostream>
#include <vector>
#include <string>
#include <boost/foreach.hpp>

class NGonRing 
{
public:
    // constructor
    NGonRing(int nGon);
	
    // Generate solutions for the total requested
    bool generateSolutions(
		int totalPerLine, 
		std::vector<std::string> &nGonRingSolutions
		) const; 

	// Generate solutions for the total
	bool generateSolutions( 
		int totalPerLine, std::vector<std::vector<int> > &nGonRingSolutions
		) const;

    
    // Generate all solutions
    bool generateSolutions(
		std::vector<std::string> &nGonRingSolutions
		) const; 

	// Is the solution a valid solution
	bool isValidSolution( 
		const std::vector<int> &solution, 
		int totalPerLine = -1 ) const;
 
	// Check if the solution already exist 
	bool isCyclicWithExisting(
		const std::vector<int> solution, 
		const std::vector<std::vector<int> > &nGonRingSolutions
		) const;

	// sort the solution such that smallest set is in the beginning
	void sortTheSolution(std::vector<int> &solution) const;

	// Convert permutation to solution
	bool convertPermutationToSolution(
		const std::vector<int> &regularPermutation,
		std::vector<int> &possibleSolutions
		) const;

private:
    int _nGon; // size of this ring
	int _totalDigits; // total number of digits
};

std::string convertVectorToString(const std::vector<int> &solutionVector);

std::string int2String(int n);

bool displaySolutions(
    int nGon, int totalPerLine, 
    const std::vector<std::string> &nGonRingSolutions
    );

bool displaySolutions(
    int nGon, int totalPerLine, 
    const std::vector<std::vector<int> > &nGonRingSolutions
    );

template<class EntryType>
void displayVector(const std::vector<EntryType> &vec)
{
	std::cout << "( ";
	BOOST_FOREACH( EntryType entry, vec )
		std::cout << entry << " , ";
	std::cout << " )" << std::endl;
}

#endif // _NGONRING_H_

