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
#include <algorithm>
#include <vector>
#include <numeric>
#include <list>

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


int sumOfDigits(vlong num)
{
	int sum = 0;
	while(num > 0)
	{
		sum += num%10;
		num /= 10;
	}
	return sum;
}

bool isNonDigit(int num)
{
	return (num < 0 && num > 9);
}

int numOfDigits(vlong num)
{
	int count = 0;
	while(num > 0)
	{
		count++;
		num /= 10;
	}
	return count;
}

bool isPartitionValid(const vector<int> &partition,
					  const vlong &lLimit,
					  const vlong &uLimit)
{
	if( find_if(partition.begin(), partition.end(), isNonDigit) != 
		partition.end() )
		return false;

	if(partition.size() > uLimit)
		return false;

	return true;
}

bool nextPartition(vector<int> &partition, 
				   const vlong &lLimit,
				   const vlong &uLimit)
{
	// partition algorithm is as follows (produces partitions in 
	// lexicographically descending order
	// * find the right most number greater than 1 in the partition list
	// * subtract 1 from it
	// * keeping the descending order intact, try to compress rest of the 
	//   numbers 
	// * if you can't then find the next number greater than 1 in the partition
	//   list
	auto currentItem = partition.end();
	for(auto it = partition.begin(); it != partition.end(); ++it)
		if(*it > 1)
			currentItem = it;

	while(currentItem != partition.end())
	{
		vector<int> newPartition;
		copy(partition.begin(), currentItem-1, back_inserter(newPartition));
		newPartition.push_back(*currentItem - 1);
		int restOfTheNumbers = 1; // start with the subtracted 1
		accumulate(currentItem + 1, partition.end(), restOfTheNumbers);

		while(restOfTheNumbers > 1)
		{
			if(restOfTheNumbers >= *currentItem - 1)
			{
				newPartition.push_back(*currentItem - 1);
				restOfTheNumbers -= *currentItem - 1;
			}
			else
			{
				newPartition.push_back(restOfTheNumbers);
				restOfTheNumbers = 0;
			}
		}

		// validity is defined newPartition
		if(find_if(newPartition.begin(), newPartition.end(), isNonDigit) == 
		   newPartition.end())
		{ // not valid
			--currentItem;
		}
		if( isPartitionValid(newPartition, lLimit, uLimit) )
		{ // valid
			partition.clear();
			copy(newPartition.cbegin(), newPartition.cend(),
				 back_inserter(partition));
			return true; // The only time we return true
		}
		else --currentItem;
	}

	return false;
}


vlong getNumber(const list<int> &digList)
{
	vlong num = 0;
	for(auto dig : digList)
		num = num*10 + dig;
	return num;
}

bool permutationNotLargeEnough(const list<int> &perm, vlong A)
{
	vlong num = getNumber(perm);
	return A > num;
}

bool permutationNotSmallEnough(const list<int> &perm, vlong B)
{
	vlong num = getNumber(perm);
	return B < num;
}

bool constructMinimumSortedPartition(list<int> &partition, vlong A, vlong B)
{
	int Asize = numOfDigits(A);
	if( partition.size() < Asize )
	{
		int diff = Asize - partition.size();
		int front = partition.back();
		partition.pop_back();
		for(int i = 0; i < diff; i++)
			partition.push_back(0);

		partition.sort();
		// put the smallest at the front of the list
		partition.push_front(front);
	}
	else
	{
		partition.sort();
	}

	while(permutationNotLargeEnough(partition, A))
		next_permutation(partition.begin(), partition.end());

	int Bsize = numOfDigits(B);
	if(partition.size() < Bsize)
	{
		int diff = Bsize - partition.size();
		for(int i = 0; i < diff; i++)
			partition.push_front(0);
	}

	vlong num = getNumber(partition);
	if(num >= A && num <= B)
		return true;
	else
		return false;
}

vlong countNumberOfPermutations(const vector<int> &partition, vlong A, vlong B)
{
	vlong count = 0;

	list<int> copyPartition(partition.begin(), partition.end());

	int Asize = numOfDigits(A);

	if(constructMinimumSortedPartition(copyPartition, A, B))
			count++;

	while(next_permutation(copyPartition.begin(), copyPartition.end()))
	{
		if(permutationNotSmallEnough(copyPartition, B))
			break;
		else
			++count;
	}

	return count;
}


vlong countLuckyNumbers(vlong A, vlong B, const vector<int> primeVec)
{
	vlong count = 0;
	int Asum = sumOfDigits(A);
	int Bsum = sumOfDigits(B);
	for(auto prime: primeVec)
	{
		vector<int> partition;
		partition.push_back(prime);
		while(nextPartition(partition, A, B))
		{
			if( isPrime(sumOfSquares(partition)) )
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

