#include <iostream>
#include <bitset>
#include <climits>

using namespace std;

bool is_equal(int a, int b) {
  int a_1[10], b_1[10];
  for(int i = 0; i < 10; i++)
    a_1[i] = b_1[i] = 0;

  while(a > 0 && b > 0) {
    a_1[a%10]++;
    b_1[b%10]++;
    a /= 10;
    b /= 10;
  }
  if(a > 0 || b > 0) return false;

  for(int i = 0; i < 10; i++)
    if(a_1[i] != b_1[i]) return false;

  return true;
}

bool is_equal_upto_6x(int x) {
  if(is_equal(x,2*x) && is_equal(x, 3*x) && is_equal(x, 4*x) && 
     is_equal(x, 5*x) && is_equal(x, 6*x)) {
    cout << x << " " << 2*x << " " << 3*x << " "<< 4*x << " " << 5*x << " "
	 << 6*x << endl;
    return true;
  }
  return false;
}

int n_digits(int n) {
  int d = 0;
  while(n > 0) {
    n/=10;
    d++;
  }
  return d;
}

int num_x_6x() {
  for(int i = 10; i < INT_MAX; i *= 10) {
    for(int j = i; 6*j < i*10; j++) {
      if(is_equal_upto_6x(j)) return j;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  cout << num_x_6x() << endl;
  return 0;
}


