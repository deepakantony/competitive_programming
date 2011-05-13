#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

template<typename T>
void _swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}
  

template<typename IT>
void reverse(IT begin, IT end) {
  while(begin < end)
    _swap(*begin++, *(--end));
}
    

class vlong {
public:
  vlong(const vlong &n) {
    data.clear();
    data = n.data; //(n.data.begin(), n.data.end());
  }
  vlong(int n = 0) {
    data.clear();
    while(n>0) {
      data.push_back(n%10);
      n /= 10;
    }
  }

  vlong& operator+=(const vlong &n) {
    vector<char>::const_iterator l_it = data.begin(), lend = data.end();
    vector<char>::const_iterator s_it = n.data.begin(), send = n.data.end();
    if(data.size() < n.data.size()) {
      l_it = n.data.begin();
      lend = n.data.end();
      s_it = data.begin();
      send = data.end();
    }
    vector<char> new_data;
    int carry = 0;
    int sum;
    while(l_it != lend) {
      sum = carry;
      if(s_it != send) {
	sum += *s_it;
	s_it++;
      }
      sum += *l_it;
      l_it++;

      new_data.push_back(sum%10);

      carry = sum/10;
    }

    while(carry != 0) {
      new_data.push_back(carry%10);
      carry /= 10;
    }

    this->data.clear();
    this->data = new_data;

    return *this;
  }

  const vlong operator+(const vlong &n) const {
    return vlong(*this) += n;
  }

  const vlong operator+(const int &n) const {
    return vlong(*this) += n;
  }

  vlong& operator+=(const int &n) {
    return *this += vlong(n);
  }

  vlong& operator*=(const vlong &n) {
    vector<char> new_data;
    int i = 0;
    for(vector<char>::const_iterator it = data.begin(); 
	it != data.end(); it++, i++) {
      int carry = 0;
      int prod;
      int k = i;
      for(vector<char>::const_iterator it_2 = n.data.begin();
	  it_2 != n.data.end(); it_2++, k++) {
	prod = *it * (*it_2) + carry;
	if(k >= new_data.size())
	  new_data.push_back(prod%10);
	else {
	  prod += new_data[k];
	  new_data[k] = prod%10;
	}
	carry = prod/10;
      }
      while(carry > 0) {
	if(k >= new_data.size())
	  new_data.push_back(carry%10);
	else {
	  carry += new_data[k];
	  new_data[k] = carry%10;
	}
	carry /= 10;
      }
    }
    this->data.clear();
    this->data = new_data;
    return *this;
  }

  const vlong operator*(const vlong &n) const {
    return vlong(*this) *= n;
  }

  vlong& operator*=(const int &n) {
    return *this *= vlong(n);
  }

  const vlong operator*(const int &n) const {
    return vlong(*this) *= vlong(n);
  }

  string to_string() const {
    string res;
    for(vector<char>::const_iterator it = data.begin(); it != data.end();
	it++)
      res += (*it + '0');

    reverse(res.begin(), res.end());
    return res;
  }

  long sum_of_digits() const {
    long res = 0;
    for(vector<char>::const_iterator it = data.begin(); it != data.end(); it++)
      res += (*it);
    return res;
  }
    
private:
  vector<char> data;
};

ostream& operator<<(ostream &out, const vlong &n) {
  out << n.to_string() << " " << n.sum_of_digits();
  return out;
}

int main(int argc, char **argv) {
  int n = atoi(argv[1]);

  vlong prev_2 = 1;
  vlong prev_1 = 2;
  for(int i = 1, k = 1; i < n; i++) {
    vlong cur;
    if( (i+1)%3 == 0)
      cur = prev_1 * k++ * 2 + prev_2;
    else
      cur = prev_2 + prev_1;
    prev_2 = prev_1;
    prev_1 = cur;
    cout << cur << endl;
  }
  return 0;
}
    
