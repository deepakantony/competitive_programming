#include <iostream>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

int p(int n) {
  return n*(3*n-1)/2;
}

bool is_pentagonal(int p){
  double sqrt_1_24p = sqrt(1+24*p);
  if(ceil(sqrt_1_24p) != floor(sqrt_1_24p) )
    return false;

  return ((((int)ceil(sqrt_1_24p)+1)%6) == 0);
}

int main(int argc, char **argv) {
  int D = INT_MAX;
  int _pi, _pj, _i, _j;

  vector<int> P;
  P.push_back(0);
  P.push_back(1);
  P.push_back(p(2));

  for(int i = 2; P[i] < INT_MAX && P[i]-P[i-1] < D; i++) {
    for(int j = i-1; j > 0 && P[j]-P[i] < D; j--) {
      if(is_pentagonal(P[i]+P[j]) && is_pentagonal(P[i]-P[j])) {
	D = P[i]-P[j];
	_pi = P[i]; _pj = P[j]; _i = i; _j = j;
	cout << D << endl;
	return 0; // i need to figure out how to be certain the minimality of this D
      }
    }
    P.push_back(p(i+1));
  }

  cout << D << endl;
  cout << _i << " " << _j << " " << _pi << " " << _pj << endl;

  return 0;
}
