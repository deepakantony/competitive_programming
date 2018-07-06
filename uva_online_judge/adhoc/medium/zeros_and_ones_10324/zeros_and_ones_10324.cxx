#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  string s;
  int c = 1;

  while((cin>>s) && !s.empty()) {
    vector<int> v(s.size()+1);
    v[0] = 0;
    for(int i = 0; i < s.size(); ++i)
      v[i+1] = v[i]+int(s[i]-'0');

    cout << "Case " << c << ":\n";
    int q; cin >> q;
    while(q--) {
      int i,j; cin >> i >> j; if(i>j)swap(i,j);
      if(v[i] == v[j+1] || // case for 0
	 (v[j+1]-v[i]) == (j-i+1))
	cout << "Yes\n";
      else cout << "No\n";
    }

    ++c;
  }

  return 0;
}
