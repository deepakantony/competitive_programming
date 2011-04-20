#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <algorithm>

using namespace std;

bool is_square(int n) {
  double sqrt_n = sqrt((double)n);
  return ceil(sqrt_n) == floor(sqrt_n);
}

vector<int> irrational_square_root(const int &n) {
  if( is_square(n) ) 
    throw "A square is not an irrational number!";

  vector<int> res;
  res.push_back(floor(sqrt(double(n))));
  int term2 = 0;
  int denom = 1;

  do {
    int new_term2 = denom*(*(res.end()-1)) - term2;
    int new_denom = (n-(new_term2*new_term2))/denom;
    res.push_back((res[0]+new_term2)/new_denom);
    term2 = new_term2;
    denom = new_denom;
    //cout << term2 << " " << denom <<  " : " << res[0] << endl;
  }while(term2 != res[0] || denom != 1);

  return res;
}

int main(int argc, char **argv) {
  int limit = atoi(argv[1]);
  int count = 0;
  for(int i = 1; i <= limit; i++) {
    if(!is_square(i)) {
      vector<int> fraction_rep = irrational_square_root(i);

      if((fraction_rep.size()-1)%2) {
	count++;
	cout << "[" << fraction_rep[0] << ";(";
	copy(fraction_rep.begin()+1, fraction_rep.end()-1,
	     ostream_iterator<int>(cout, ","));
	cout << *(fraction_rep.end()-1) << ")]" << endl;
      }
    }
  }

  cout << count << endl;

  return 0;
}
    
