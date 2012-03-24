#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

string to_string(int n) {
  string res;
  while(n>0) {
    res += n%10+'0';
    n /= 10;
  }
  reverse(res.begin(), res.end());
  return res;
}

struct vlong {
  vlong(string str_n) : _data(str_n) {}
  vlong(const vlong &n): _data(n._data) {}
  vlong(int n): _data(to_string(n)) {}

  vlong& operator+=(const vlong &n) {
    string num1 = this->_data;
    string num2 = n._data;
    string res;

    if(num1.size() < num2.size())
      swap(num1, num2);
    
    string::reverse_iterator it1 = num1.rbegin();
    string::reverse_iterator it2 = num2.rbegin();
    char carry = 0;
    while(it1 < num1.rend()) {
      char sum = *it1-'0' + carry;
      if(it2 < num2.rend()) {
	sum += *it2-'0';
	it2++;
      }
      res += sum%10+'0';
      carry = sum/10;
      it1++;
    }
    while(carry > 0) {
      res += carry%10+'0';
      carry /= 10;
    }
    reverse(res.begin(), res.end());
    this->_data = res;
    return *this;
  }
  const vlong operator+(const vlong &n) const { return vlong(*this) += n; }

  vlong& operator*=(const vlong &n) {
    string res;
    int i = 0;
    string n_data = n._data;
    for(string::reverse_iterator it1 = _data.rbegin(); 
	it1 < _data.rend(); it1++, i++) {
      int k = i;
      int carry = 0;
      for(string::reverse_iterator it2 = n_data.rbegin();
	  it2 < n_data.rend(); it2++, k++) {
	int prod = (*it1-'0') * ((*it2)-'0') + carry;
	if(k >= res.size())
	  res += (char)(prod%10)+'0';
	else {
	  prod += res[k]-'0';
	  res[k] = (char)(prod%10)+'0';
	}
	carry = prod/10;
      }
      while(carry > 0) {
	if(k >= res.size())
	  res += (char)(carry%10)+'0';
	else {
	  carry += res[k]-'0';
	  res[k] = (char)(carry%10)+'0';
	}
	carry /= 10;
	k++;
      }
    }
    reverse(res.begin(), res.end());
    this->_data = res;

    return *this;
  }
  const vlong operator*(const vlong &n) const { return vlong(*this) *= n; }

  bool operator==(const vlong &n) const { return _data.compare(n._data)==0;}
  bool operator!=(const vlong &n) const { return !(*this == n); }

  bool isodd() const {
    if(_data.size() == 0) return false;
    return _data[_data.size()-1] % 2 != 0;
  }
  bool iseven() const { return !isodd(); }

  const vlong pow(const int n) const {
    if(n == 0) return vlong("1");
    if(n == 1) return vlong(*this);
    if(n == 2) return vlong(*this) * vlong(*this);
    if(n%2 != 0) return vlong(*this) * ((this->pow((n-1)/2)).pow(2));
    return (this->pow(n/2)).pow(2);
  }

  int sum_of_digits() const {
    int sum = 0;
    for(string::const_iterator it = _data.begin(); it != _data.end(); it++)
      sum += *it - '0';
    return sum;
  }

  string _data;
};

ostream& operator<<(ostream &out, const vlong &n) {
  out << n._data;
  return out;
}

int main(int argc, char **argv) { 
  int max = 0;
  for(int i = 2; i < 100; i++) {
    vlong n(i);
    vlong pow("1");
    for(int j = 1; j < 100; j++) {
      pow *= n;
      int sum = pow.sum_of_digits();
      if(sum > max) max = sum;
    }
  }
  cout << max << endl;
  return 0;
}

