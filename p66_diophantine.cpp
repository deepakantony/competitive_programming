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
    res += (n%10 + '0');
    n/=10;
  }
  return res;
}

class vlong {
public:
  vlong(){}
  vlong(int n):_data(to_string(n)) {}
  vlong(string data) {
    reverse(data.begin(),data.end());
    _data = data;
  }
  vlong(const vlong &n) : _data(n._data) {}

  vlong& operator+=(const vlong &n) { 
    string res;
    string::const_iterator it_l = this->_data.begin(), l_end = _data.end();
    string::const_iterator it_s = n._data.begin(), s_end = n._data.end();
    if(_data.size() < n._data.size()) {
      it_l = n._data.begin(); l_end = n._data.end();
      it_s = _data.begin(); s_end = _data.end();
    }
    
    int carry = 0;
    int sum = 0;
    while(it_l != l_end) {
      if(it_s != s_end) {
	sum += *it_s - '0';
	it_s++;
      }
      sum += (*it_l + carry - '0');
      carry = sum/10;
      res += sum%10 + '0';
      sum = 0;
      it_l++;
    }
    while(carry > 0) {
      res += carry%10+'0';
      carry /= 10;
    }

    this->_data = res;

    return *this; 
  }
  vlong& operator+=(const int &n) { return *this += vlong(n); }
  const vlong operator+(const vlong &n) const { return vlong(*this)+=n; }
  const vlong operator+(const int &n) const { return vlong(n)+= *this; }
  friend const vlong operator+(const int &num, const vlong &n);

  vlong& operator*=(const vlong &n) { 
    string res;

    int i = 0;
    for(string::const_iterator it = _data.begin(); it != _data.end(); it++, i++) {
      int k = i;
      int carry = 0;
      for(string::const_iterator it_s = n._data.begin(); it_s != n._data.end(); it_s++, k++) {
	int prod = (*it-'0') * (*it_s-'0') + carry;
	if(k < res.size()) {
	  prod += res[k]-'0';
	  res[k] = prod%10 + '0';
	}
	else {
	  res += prod%10 + '0';
	}
	carry = prod/10;
      }
      while(carry > 0) {
	if(k < res.size()) {
	  carry += res[k]-'0';
	  res[k] = carry%10 + '0';
	}
	else
	  res += carry%10 + '0';

	carry /= 10;
      }
    }
    this->_data = res;

    return *this; 
  }
  vlong& operator*=(const int &n) { return *this *= vlong(n); }
  const vlong operator*(const vlong &n) const { return vlong(*this)*=n; }
  const vlong operator*(const int &n) const { return vlong(n)*= *this; }
  friend const vlong operator*(const int &num, const vlong &n);

  bool operator>(const vlong &n) const {
    if(_data.size() > n._data.size())
      return true;
    else if(_data.size() < n._data.size())
      return false;
    for(int i = 0; i < _data.size(); i++) 
      if(_data[i] > n._data[i])
	return true;
      else if(_data[i] < n._data[i])
	return false;

    return false;
  }
  bool operator>(const int &n) const { return *this > vlong(n); }

  vlong& operator=(const vlong &n) {
    _data.clear();
    _data = n._data;
    return *this;
  }

  vlong& operator=(const int &n) {
    _data.clear();
    _data = to_string(n);
    return *this;
  }

  friend ostream& operator<<(ostream &out, const vlong &n);
private:
  string _data;
};

const vlong operator+(const int &num, const vlong &n) {
  return vlong(num) += n;
}

const vlong operator*(const int &num, const vlong &n) {
  return vlong(num) *= n;
}

ostream& operator<<(ostream &out, const vlong &n) {
  string data(n._data);
  reverse(data.begin(), data.end());
  cout << data;
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

  vlong pn, pn_1, pn_2, qn, qn_1, qn_2;
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
