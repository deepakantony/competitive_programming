#include "NGonRing.h"
#include <vector>
#include <string>

using namespace std;

//
// Constructor
NGonRing::NGonRing(int nGon)
	:_nGon(nGon)
{
}


//
// Generate solutions for the total
bool NGonRing::generateSolutions( 
	int totalPerLine, vector<string> &nGonRingSolutions
	) const
{
	return true;
}

// 
// Our special display function
bool displaySolutions (
	int nGon, int totalPerLine, const vector<string> &nGonRingSolutions
	)
{
	return true;
}

