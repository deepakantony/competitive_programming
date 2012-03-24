#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  int limit = atoi(argv[1]);
  int count = 0;
  for(int n = 1; n <= 100; n++) {
    int r = 0;
    int nCr = 1;
    int nby2 = n/2;
    while(nCr < limit && r < nby2) {
      nCr = nCr*(n-r)/(r+1);
      r++;
    }

    if(nCr > limit) 
      count += (n-2*r+1);
  }

  cout << count << endl;

  return 0;
}
