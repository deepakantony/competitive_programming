#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main()
{
  int N; 
  bool first = true;
  while(cin >> N) {
    if(first) first = false;
    else cout << "\n";
    map<string,int> net_worth;
    vector<string> names;

    for(int i = 0; i < N; ++i) {
      string name; cin >> name;
      net_worth[name] = 0;
      names.push_back(name);
    }

    for(int i = 0; i < N; ++i) {
      string giver; cin >> giver;
      int gift; cin >> gift;
      int p; cin >> p;
      int gift_per_p = 0;
      if(p>0) gift_per_p = gift/p;

      while(p--) {
	string taker; cin >> taker;
	net_worth[giver] -= gift_per_p;
	net_worth[taker] += gift_per_p;
      }
    }
    
    for(auto name : names)
      cout << name << " " << net_worth[name] << "\n";
  }

  return 0;
}
