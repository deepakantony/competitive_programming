// A number is called lucky if the sum of its digits, as well as the sum of the 
// squares of its digits is a prime number. How many numbers between A and B are 
// lucky?
// Input:
// The first line contains the number of test cases T. Each of the next T lines 
// contains two integers, A and B.
// Output:
// Output T lines, one for each case containing the required answer for the 
// corresponding case.
// 
// Constraints:
// 1 <= T <= 10000
// 1 <= A <= B <= 10^18
// Sample Input:
// 2
// 1 20
// 120 130
// Sample Output:
// 4
// 1
// Explanation:
// For the first case, the lucky numbers are 11, 12, 14, 16.
// For the second case, the only lucky number is 120.
//

#include <iostream>
#include <string>

using namespace std;

#define MAX_SUM_OF_SQUARES 1459 // (18 * 9 * 9) + 1

int primes[MAX_SUM_OF_SQUARES+1];

void initPrimes()
{
	primes[0] = primes[1] = 0;
	for(int index = 2; index <= MAX_SUM_OF_SQUARES; index++)
		primes[index] = -1;

	for(int index = 2; index <= MAX_SUM_OF_SQUARES; )
	{
		primes[index] = 1;
		int index2 = 2*index;
		while(index2 <= MAX_SUM_OF_SQUARES)
		{
			primes[index2] = 0;
			index2 += index;
		}

		while(index <= MAX_SUM_OF_SQUARES && primes[index] != -1)
			index++;
	}
}	

bool isPrime(int num)
{
	return (num <= MAX_SUM_OF_SQUARES && primes[num] == 1)?true:false;
}

class BigNum
{
private:
	string data;
public:
	BigNum(string num): data(num) {}

	BigNum& operator++() {
		int size = this->data.size();

		int carry = 1;
		for(int index = size-1; index >= 0; index--)
		{
			this->data[index]++;
			if(this->data[index] > '9') 
			{
				this->data[index] = '0';
				carry = 1;
			}
			else
			{
				carry = 0;
				break;
			}
		}
		if(carry == 1)
			this->data = string("1") + this->data;

		return *this;
	}
	
	bool operator<=(const BigNum& num) const {
		int size1 = this->data.size();
		int size2 = num.data.size();

		if(size1 > size2)
			return false;
		if(size2 > size1)
			return true;
		
		for(string::const_iterator it1 = this->data.begin(),
				it2 = num.data.begin();
			it1 != this->data.end() && it2 != num.data.end();
			it1++, it2++)
		{
			if ( *it1 > *it2 )
				return false;
			if ( *it2 > *it1 )
				return true;
		}

		return true;
	}

	void sumAndSquareSum(int &sum, int &squareSum) {
		sum = 0;
		squareSum = 0;
		int dig;
		for(string::const_iterator it = this->data.begin();
			it != this->data.end(); it++)
		{
			dig = *it - '0';
			sum += dig;
			squareSum += dig*dig;
		}
	}

	bool isLucky() {
		int sum, squareSum;
		this->sumAndSquareSum(sum, squareSum);
		return (isPrime(sum) && isPrime(squareSum)) ? true: false;
	}

	void print() {
		cout << this->data << endl;
	}
};

int main(int argc, char *argv[])
{
	initPrimes();
	int nTests;
	cin >> nTests;
	string strA, strB;
	int luckyNums = 0;
	int sum, squareSum;
	for(int index = 0; index < nTests; index++)
	{
		cin >> strA;
		BigNum A(strA);

		cin >> strB;
		BigNum B(strB);

		luckyNums = 0;
		while( A <= B) {
			if (A.isLucky()) 
			{
				luckyNums++;
			}
			++A;
		}

		cout << luckyNums << endl;
	}

	return 0;
}

