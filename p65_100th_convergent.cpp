#include <iostream>
#include <cstdlib>

using namespace std;

typedef unsigned long long vlong;

int main(int argc, char **argv) {
  int n = atoi(argv[1]);

  vlong prev_2 = 1;
  vlong prev_1 = 2;
  for(int i = 1, k = 1; i < n; i++) {
    vlong cur;
    if( (i+1)%3 == 0)
      cur = prev_1*k++ * 2 + prev_2;
    else
      cur = prev_2 + prev_1;
    prev_2 = prev_1;
    prev_1 = cur;
    cout << cur << endl;
  }
  return 0;
}
    
