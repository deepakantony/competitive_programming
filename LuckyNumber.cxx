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

//
// Here's an idea of how this could be done in shorter time
// * loop through all primes that are less than or equals 17*(9^2)
// * for each primes we calculate partitions 
//        * A partition can only have digits
//        * So now, we have set which we can permute, insert 0's and constrain it
//          to be within A and B
// * The total of these will give us the answer


#include <iostream>
#include <string>

using namespace std;

#define MAX_SUM_OF_SQUARES 1459 // (18 * 9 * 9) + 1
#define MAX_SUM_OF_DIGITS 163 // (18 * 9) + 1

typedef unsigned long long vlong;

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

void buildPrimeVector(vector<int> &primeVec)
{
	primeVec.clear();
	primeVec.push_back(2);
	for(int num = 3; num < MAX_SUM_OF_DIGITS; num+=2)
	{
		if(isPrime(num))
			primeVec.push_back(num);
	}
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


int sumOfSquares(const vector<int> &vec)
{
	int sum = 0;
	for(auto num: vec)
	{
		sum += num * num;
	}
	return sum;
}

bool nextPartition(vector<int> &partition)
{
	// partition algorithm is as follows (produces partitions in 
	// lexicographically descending order
	// * find the right most number greater than 1 in the partition list
	// * subtract 1 from it
	// * keeping the descending order intact, try to compress rest of the 
	//   numbers 
	// * if you can't then find the next number greater than 1 in the partition
	//   list
}

vlong countLuckyNumbers(vlong A, vlong B, const vector<int> primeVec)
{
	vlong count = 0;
	for(auto prime: primeVec)
	{
		vector<int> partition;
		partition.push_back(prime);
		while(nextPartition(partition))
		{
			if( sumOfSquares(partition) == prime )
			{
				count += countNumberOfPermutations(partition, A, B);
			}
		}
	}
	return count;
}

int main(int argc, char *argv[])
{
	initPrimes();
	vector<int> primeVec;
	buildPrimeVector(primeVec);
	int nTests;
	cin >> nTests;
	vlong A, B;

	int sum, squareSum;
	for(int index = 0; index < nTests; index++)
	{
		cin >> A >> B;
		cout << countLuckyNumbers(A, B, primeVec) << endl;
	}

	return 0;
}

