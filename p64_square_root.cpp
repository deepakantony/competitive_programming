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

  int term2 = res[0];
  int denom = 1;

  do {
    int new_denom = (n-(term2*term2))/denom;
    if(new_denom == 1)
      res.push_back(term2 + res[0]);
    else
      res.push_back(ceil((double)term2/(double)new_denom));
    term2 = new_denom - term2%new_denom;
    denom = new_denom;
  }while(term2 != res[0]);

  return res;
}

int main(int argc, char **argv) {
  int limit = atoi(argv[1]);

  vector<int> fraction_rep = irrational_square_root(limit);

  cout << "[" << fraction_rep[0] << ";(";
  copy(fraction_rep.begin()+1, fraction_rep.end()-1,
       ostream_iterator<int>(cout, ","));
  cout << *(fraction_rep.end()-1) << ")]" << endl;

  return 0;
}
    
