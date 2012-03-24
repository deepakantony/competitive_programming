#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

bool operator>(const string &num1, const string &num2);
int numOfDigits(int n);
int numOfDigits(vector<int> vec);

class NGonRing {
public:
  NGonRing(int max, int sum, int nDigits, nGon):
    max(max), sum(sum), nDigits(nDigits), nGon(nGon) {
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
  
  void generateMagicRings();

  int max, sum, nDigits, nGon;
  vector<string> magicRings;
};


void NGonRing::generateMagicRings()
{
  vector< vector<int> > numberSums;
  vector<int> curSum;
  // construct the 3 number set that adds up to "sum"
  for(int n = 1; n <= max; n++) { // Loop through all numbers
    for(int secondN = 1; secondN <= max; secondN++){
      if(n == secondN) continue;

      for(int thirdN = 1; thirdN <= max; thirdN++){
	if(n == thirdN || secondN == thirdN) continue;
	if((n+secondN+thirdN) == sum){
	  curSum.push_back(n);
	  curSum.push_back(secondN);
	  curSum.push_back(thirdN);
	  numberSums.push_back(curSum);
	  curSum.clear();
	}
      }
    }
  }

  for(int i = 0; i < numberSums.size(); i++) {

    // NEED TO PERFORM BACKTRACKING HERE
    for(int j = 0; j < numberSums.size() && n_gon < this->nGon; j++) {
    
    }
}



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
    cout << "Usage: <program> <max_fill_number> <num_digits> <n_gon>" 
	 << endl;
    return -1;
  }

  int maxFillNumber, numDigits, nGon;
  maxFillNumber = atoi(argv[1]);
  numDigits = atoi(argv[2]);
  nGon = atoi(argv[3]);

  if(!maxFillNumber || !numDigits) {
    cout << "All arguments must be integers" << endl;
    return -1;
  }

  string largestMagicRing;
  int minSum = (maxFillNumber/2)*3;
  int maxSum = ((maxFillNumber/2)+1)*3;
  cout << "Mininum sum: " << minSum << " - Maximum sum: " << maxSum << endl;
  for(int sumPerRow = minSum; sumPerRow <= maxSum; sumPerRow++) {
    NGonRing rings(maxFillNumber, sumPerRow, numDigits, nGon);
    string largest = rings.largestMagicRing();
    if( largest > largestMagicRing )
      largestMagicRing = largest;
    cout << rings << endl;
  }


  cout << "Largest: " << largestMagicRing << endl;

  return 0;
}
