#include <iostream>
#include <map>
#include <set>

using namespace std;

int main()
{
  int k, m;
  while((cin>>k>>m)) {
    bool can_complete=true;
    set<int> s;
    for(int i=0; i < k; ++i) {
      int course; cin >> course;
      s.insert(course);
    }

    for(int i=0; i<m; ++i) {
      int r,req,course;
      cin >> r >> req;
      while(r--) {
	cin >> course;
	if(s.find(course)!=s.end())
	  req--;
      }
      if(req>0) can_complete = false;
    }
    cout << (can_complete ? "yes" : "no") << "\n";
  }

  return 0;
}
