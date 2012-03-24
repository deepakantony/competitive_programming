#include "NGonRing.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]) 
{
	if(argc != 3)
	{
		cout << "Usage: " << argv[0] << " <sizeOfTheRing> <totalPerLine>" 
			 << endl;
		return -1;
	}

	int nGon = atoi(argv[1]);
	int totalPerLine = atoi(argv[2]);

	// Create a ring and generate solution for the total requested
	NGonRing theRing(nGon);
	vector<vector<int> > nGonRingSolutions;
	theRing.generateSolutions(totalPerLine, nGonRingSolutions);

	// Custom display of solutions
	displaySolutions(nGon, totalPerLine, nGonRingSolutions);

	return 0;
}

