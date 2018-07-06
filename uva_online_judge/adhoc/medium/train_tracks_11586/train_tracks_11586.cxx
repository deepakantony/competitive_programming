#include <iostream>
#include <string>

using namespace std;

int main()
{
  int T; cin >> T; char c; while(cin.get(c) && c != '\n') continue;
  while(T--) {
    string s;
    getline(cin, s);
    int Ms = 0, Fs = 0;
    for(auto v: s)
      if(v=='M') Ms++;
      else if(v=='F') Fs++;

    if(Ms==Fs && Ms != 1) cout << "LOOP\n";
    else cout << "NO LOOP\n";
  }
  return 0;
}
