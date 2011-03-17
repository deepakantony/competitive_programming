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

  for(int i = 2; i < INT_MAX; i++) {
    P.push_back(p(i));
    if(P[i] )

  cout << D << endl;
  cout << _i << " " << _j << " " << _pi << " " << _pj << endl;

  return 0;
}
