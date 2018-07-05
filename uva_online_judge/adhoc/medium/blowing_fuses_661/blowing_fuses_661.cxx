#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
  int n,m,c,cap[22],state[22], seq = 1;
  while((cin >> n >> m >> c) && !(n==0 && m==0 && c==0)) {
    memset(state, 0, sizeof(state));

    for(int i = 0; i < n; ++i)
      cin >> cap[i];

    int cur_c = 0;
    int max_c = 0;
    bool fuse_blown = false;
    for(int i = 0; i < m; ++i) {
      int d; cin >> d; d--;
      state[d] ^= 1; // flip bit

      if(state[d]) cur_c += cap[d];
      else cur_c -= cap[d];

      if(cur_c > c) fuse_blown = true;
      max_c = max(cur_c, max_c);
    }

    cout << "Sequence " << seq << "\n";
    if(fuse_blown)
      cout << "Fuse was blown.\n";
    else
      cout << "Fuse was not blown.\n"
	   << "Maximal power consumption was " << max_c << " amperes.\n";

    cout << "\n";
    ++seq;
  }
  return 0;
}
