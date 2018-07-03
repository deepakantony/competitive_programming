#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
  int T; cin >> T;
  int sal[3];
  for (int i = 0; i < T; ++i ) {
    cin >> sal[0] >> sal[1] >> sal[2];
    sort(sal, sal+3);
    cout << "Case " << i + 1 << ": " << sal[1] << "\n";
  }

  return 0;
}
