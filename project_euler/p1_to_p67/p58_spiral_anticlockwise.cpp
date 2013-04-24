#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long unsigned int vlong;

bool is_prime(vlong n) {
  if(n == 2 || n == 3 || n == 5 || n == 7)
    return true;
  if(n < 11) return false;
  if(n%2 == 0 || n%3 == 0) return false;

  vlong sqrt_n = ceil(sqrt(n));
  for(vlong i = 5; i <= sqrt_n; i+=6) {
    if(n%i == 0) return false;
    if(n%(i+2) == 0) return false;
  }
  return true;
}

int main(int argc, char **argv) {
  int n_prime = 0;
  int n_non_prime = 1;
  vlong num = 3;
  vlong step = 2;

  int limit_percent = atoi(argv[1]);
  int percent = 100;
  while(percent >= limit_percent) {
    for(int i = 0; i < 3; i++) {
      if(is_prime(num)) n_prime++;
      else n_non_prime++;

      num += step;
    }
    n_non_prime++; // for the fourth number (its a square)

    step += 2;
    num += step;

    percent = n_prime * 100 / (n_prime+n_non_prime);

    cout << percent << "% " << n_prime << " " << n_non_prime 
	 << " " << step-1 << endl;
  }

  return 0;
}
