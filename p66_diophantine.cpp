#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned long long vlong;

bool is_square(int n) {
  double sqrt_n = sqrt((double)n);
  return (ceil(n) == floor(n));
}

bool solve_diophantine(int D, int &x, int &y) {
  vector<int> A; // continued fraction of square root of D
  cf_square_root(D, A);

  // we will use pells equation to solve diophantine equation
  // let r be period(A) -1 which is the A.size() -2
  // (x,y) = (p(r), q(r)) for r being odd
  // (x,y) = (p(2r+1), q(2r+1)) when r is even

  // Few adjustments before we commence


  int r = A.size()-2; 
}

int main(int argc, char **argv) {
  int res_D = 0;
  int res_x = 0;

  int limit = atoi(argv[1]);

  for(int i = 2; i < limit; i++) {
    if(!is_square(i)) {
      int x,y;
      solve_diophantine(i,x,y); // D = i;
      if( x > res_x) {
	res_x = x;
	res_D = i;
      }
    }
  }

  cout << "D: " << res_D << ", x: " << res_x << endl;

  return 0;
}
