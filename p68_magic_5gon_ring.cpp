#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

bool operator>(const string &num1, const string &num2);

class NGonRing {
public:
  NGonRing(int max, int sum, int nDigits):
    max(max), sum(sum), nDigits(nDigits) {
    generateMagicRings();
  }

  string largestMagicRing() {
    string largest;

    for(vector<string>::const_iterator ring = magicRings.begin();
	ring != magicRings.end(); ring++) {
      if(*ring > largest)
	largest = *ring;
    }

    return largest;
  }

  friend ostream& operator<<(ostream &out, const NGonRing& rings);

private:
  
  void generateMagicRings() {
    vector< vector<int> > numberSums;
    vector<int> curSum;
    // construct the 3 number set that adds up to "sum"
    for(int n = 0; n < max; n++) { // Loop through all numbers
      for(int secondN = 0; secondN < max; secondN++) {
	if(n == secondN) continue;

	for(int thirdN = 0; thirdN < max; thirdN++){
	  if(n == thirdN || secondN == thirdN) continue;
	  if((n+secondN+thirdN) == sum) {
	    curSum.push_back(n);
	    curSum.push_back(secondN);
	    curSum.push_back(thirdN);
	    numberSums.push_back(curSum);
	    curSum.clear();
	  }
	}
      }
    }

    
  }

  int max, sum, nDigits;
  vector<string> magicRings;
};


bool operator>(const string &num1, const string &num2) {
  if(num1.size() > num2.size())
    return true;
  if(num2.size() > num1.size())
    return false;
  for(string::const_iterator it1 = num1.begin(), it2 = num2.begin();
      it1 != num1.end() && it2 != num2.end(); it1++, it2++) {
    if(*it1 > *it2)
      return true;
    else if(*it2 > *it1)
      return false;
  }

  return false;
}

ostream& operator<<(ostream &out, const NGonRing& rings) {
  out << "(" << flush;
  copy(rings.magicRings.begin(), rings.magicRings.end(), 
       ostream_iterator<string>(out, " "));
  out << ")" << flush;
  return out;
}

int main(int argc, char *argv[]) {
  if(argc != 4) {
    cout << "Usage: <program> <max_fill_number> <sum_per_row> <num_digits>" 
	 << endl;
    return -1;
  }

  int maxFillNumber, sumPerRow, numDigits;
  maxFillNumber = atoi(argv[1]);
  sumPerRow = atoi(argv[2]);
  numDigits = atoi(argv[3]);
  
  if(!maxFillNumber || !sumPerRow || !numDigits) {
    cout << "All arguments must be integers" << endl;
    return -1;
  }

  NGonRing rings(maxFillNumber, sumPerRow, numDigits);

  cout << rings << endl;
  cout << "Largest: " << rings.largestMagicRing() << endl;

  return 0;
}
