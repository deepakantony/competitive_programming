#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

bool is_triangle(int n) {
  int sqrt_n = floor(sqrt(2*n));
  return (sqrt_n*(sqrt_n+1) == 2*n);
}

bool is_pentagonal(int n) {
  double sqrt_n = sqrt(1+24*n);
  if(ceil(sqrt_n) != floor(sqrt_n)) return false;
  return ((int)floor(sqrt_n)+1)%6 == 0;
}

bool is_hexagonal(int n) {
  double sqrt_n = sqrt(1+8*n);
  if(ceil(sqrt_n) != floor(sqrt_n)) return false;
  return ((int)floor(sqrt_n)+1)%4 == 0;
}

int H(int n) {
  return n*(2*n-1);
}

int next_tri_pent_hex(){
  int hex;
  for(int i = 144; (hex=H(i)) < INT_MAX; i++){
    if(is_pentagonal(hex) && is_triangle(hex))
      return hex;
  }
  return 0;
}

int main(int argc, char **argv) {
  cout << next_tri_pent_hex() << endl;

  return 0;
}
