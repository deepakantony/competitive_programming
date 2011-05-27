#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

string to_string(int n) {
  string res;
  while(n > 0) {
    res += (n%10);
    n/=10;
  }
  return res;
}

class vlong {
public:
  vlong(){}
  vlong(int n):_data(to_string(n)) {}
  vlong(string data) : _data(data) {}
  vlong(const vlong &n) : _data(n._data) {}

  vlong& operator+=(const vlong &n) { return *this; }
  vlong& operator+=(const int &n) { return *this += vlong(n); }
  const vlong operator+(const vlong &n) const { return vlong(*this)+=n; }
  const vlong operator+(const int &n) const { return vlong(n)+= *this; }

  vlong& operator*=(const vlong &n) { return *this; }
  vlong& operator*=(const int &n) { return *this *= vlong(n); }
  const vlong operator*(const vlong &n) const { return vlong(*this)*=n; }
  const vlong operator*(const int &n) const { return vlong(n)*= *this; }

  bool operator>(const vlong &n) const { return true; }
  bool operator>(const int &n) const { return *this > vlong(n); }

  friend ostream& operator<<(ostream &out, const vlong &n);
private:
  string _data;
};

ostream& operator<<(ostream &out, const vlong &n) {
  for(string::const_iterator it = n._data.begin(); it != n._data.end(); it++)
    out << *it + '0';
  return out;
}

bool is_square(int n) {
  double sqrt_n = sqrt((double)n);
  return (ceil(sqrt_n) == floor(sqrt_n));
}

void cf_square_root(int D, vector<int> &A) {
  int sqrt_D = floor(sqrt(D));
  A.push_back(sqrt_D);
  int term2 = 0;
  int denom = 1;

  do {
    int new_term2 = denom*(*(A.end()-1)) - term2;
    int new_denom = (D-(new_term2*new_term2))/denom;
    A.push_back((A[0]+new_term2)/new_denom);
    term2 = new_term2;
    denom = new_denom;
  }while(term2 != A[0] || denom != 1);
}

bool solve_diophantine(int D, vlong &x, vlong &y) {
  vector<int> A; // continued fraction of square root of D
  cf_square_root(D, A);

  //  cout << "A: ";
  //  copy(A.begin(), A.end(), ostream_iterator<int>(cout, " " ));
  //  cout << endl;

  // we will use pells equation to solve diophantine equation
  // let r be period(A) -1 which is the A.size() -2
  // (x,y) = (p(r), q(r)) for r being odd
  // (x,y) = (p(2r+1), q(2r+1)) when r is even

  int pn, pn_1, pn_2, qn, qn_1, qn_2;
  pn_2 = A[0];
  pn = pn_1 = A[0]*A[1] + 1;
  qn_2 = 1;
  qn = qn_1 = A[1];

  int r = A.size()-2;
  int j = 0;
  do {
    for(int i = 2; i < A.size(); i++) {
      pn = A[i]*pn_1+pn_2;
      qn = A[i]*qn_1+qn_2;
      pn_2 = pn_1;
      pn_1 = pn;

      qn_2 = qn_1;
      qn_1 = qn;

    }

    if(A.size() > 2 && r%2 == 0 && j == 0) {
      pn = A[1]*pn_1+pn_2;
      qn = A[1]*qn_1+qn_2;
      pn_2 = pn_1; pn_1 = pn;
      qn_2 = qn_1; qn_1 = qn;
    }

    j++; 
  } while(j < 2 && r%2 == 0);

  x = pn_1; y = qn_1;

  if(A.size() > 2) {
    x = pn_2; y = qn_2;
  }

  return true;
}

int main(int argc, char **argv) {
  vlong res_D = 0;
  vlong res_x = 0;

  int limit = atoi(argv[1]);

  for(int i = 2; i < limit; i++) {
    if(!is_square(i)) {
      vlong x,y;
      solve_diophantine(i,x,y); // D = i;
      cout << i << " " << x << " " << y << endl;
      if( x > res_x) {
	res_x = x;
	res_D = i;
      }
    }
  }

  cout << "D: " << res_D << ", x: " << res_x << endl;

  return 0;
}
