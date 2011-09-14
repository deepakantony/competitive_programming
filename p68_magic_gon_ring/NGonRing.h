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

private:
	int _nGon; // size of this ring
};

bool displaySolutions(
	int nGon, int totalPerLine, 
	const std::vector<std::string> &nGonRingSolutions
	);

#endif // _NGONRING_H_

