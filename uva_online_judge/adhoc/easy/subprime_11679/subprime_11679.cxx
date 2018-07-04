#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main()
{
  int B, N;
  int bnks[21];
  while ((cin >> B >> N) && (B>0 || N>0)) {
    for(int i = 1; i <= B; ++i) cin >> bnks[i];
    while(N--) {
      int d, c, v; cin >> d >> c >> v;
      bnks[d] -= v;
      bnks[c] += v;
    }

    bool possible = true;
    for(int i = 1; i <= B; ++i) if (bnks[i] < 0) {possible = false; break;}

    cout << ((possible) ? "S" : "N") << "\n";
  }
  return 0;
}
