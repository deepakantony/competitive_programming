#ifndef _NGONRING_H_
#define _NGONRING_H_

#include <vector>
#include <string>

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
    
    // Generate all solutions
    bool generateSolutions(
		std::vector<std::string> &nGonRingSolutions
		) const; 

	// Is the solution a valid solution
	bool isValidSolution( const std::vector<int> &solution ) const;

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

#endif // _NGONRING_H_

