#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

typedef long long unsigned int vlong;

bool is_triangle(vlong n) {
  vlong sqrt_n = floor(sqrt(2*n));
  return (sqrt_n*(sqrt_n+1) == 2*n);
}

bool is_pentagonal(vlong n) {
  double sqrt_n = sqrt(1+24*n);
  if(ceil(sqrt_n) != floor(sqrt_n)) return false;
  return ((vlong)floor(sqrt_n)+1)%6 == 0;
}

bool is_hexagonal(vlong n) {
  double sqrt_n = sqrt(1+8*n);
  if(ceil(sqrt_n) != floor(sqrt_n)) return false;
  return ((vlong)floor(sqrt_n)+1)%4 == 0;
}

vlong H(vlong n) {
  return n*(2*n-1);
}

vlong next_tri_pent_hex(){
  vlong hex;
  for(vlong i = 144; i < INT_MAX-1; i++){
    hex = H(i);
    if(is_pentagonal(hex)) // a hexagonal number is a triangle number
      return hex;
  }
  return 0;
}

int main(int argc, char **argv) {
  cout << next_tri_pent_hex() << endl;

  return 0;
}
