// Changing Bit
// 
// Let A and B be two N bit numbers. You are given initial values for A and B, 
// and you should write a program which processes three kinds of queries:
// 
// set_a idx x: Set A[idx] to x, where 0 <= idx < N, where A[idx] is idx'th 
// least significant bit of A.
// set_b idx x: Set B[idx] to x, where 0 <= idx < N.
// get_c idx: Print C[idx], where C=A+B, and 0<=idx<N+1.
// Input
// First line of input contains two integers N and Q consecutively 
// (1 <= N <= 100000, 1<= Q <= 500000). Second line is an N-bit binary 
// number which denotes initial value of A, and the third line is an N-bit 
// binary number denoting initial value of B. Q lines follow, each containing 
// a query as described above.
// 
// Output
// For each query of the type get_c, output a single digit 0 or 1. Output 
// must be placed in a single line.
// 
// Sample Input
// 5 5
// 00000
// 11111
// set_a 0 1
// get_c 5
// get_c 1
// set_b 2 0
// get_c 5
// 
// Sample Output
// 100
// 

// The solution for this is creating a data structure to maintain N bit numbers.
// I split the long string into 63bit blocks, which can be represented as
// long long. It is 63bit because I need to use the 64th bit for carry.
// Just using this and performing addition after each query will result in TLE
// for some test cases. So, one update the sum when required and also,  
// compute the sum upto required number of blocks. I have used a sorted set to
// keep track of all the modified blocks.

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

#define BITSIZE 63
#define N_ULLS 1

using namespace std;


typedef unsigned long long ullong;

template<class iterator_type>
ullong binaryToULLong(iterator_type begin, iterator_type end)
{
	ullong res = 0;
	int index = 0;
	for(iterator_type it = begin; it != end; ++it, ++index) 
	{
		if(*it == '1') 
		{
			res |= (1ull << index);
		}
	}

	if(index > 64)
		throw "More than 63 bits getting extracted.";

	return res;
			
}

string ullongToString(ullong n)
{
	string res;
	for(int digit = 0; digit < 64; ++digit)
	{
		if(n > 0) {
			res += '0' + n%2;
			n /= 2;
		}
		else res += '0';
	}
	reverse(res.begin(), res.end());
	return res;
}

class LongLongSumData
{
public:
	LongLongSumData(ullong dataA, ullong dataB, int prevCarryOver = 0) 
		: _dataA(dataA), _dataB(dataB), _sum(dataA+dataB+prevCarryOver), 
		  _modified(false), _prevCarryOver(prevCarryOver) {
		updateCarry();
	}

	const int operator[](int bitIndex) const {
		if ( (_sum & ( 1ull << bitIndex )) > 0 )
			return 1;
		else
			return 0;
	}

	bool changeBitA(int bitIndex, int val) {
		return changeBit(_dataA, bitIndex, val);
	}

	bool changeBitB(int bitIndex, int val) {
		return changeBit(_dataB, bitIndex, val);
	}

	bool updateSum(int carry = 0) {
		_prevCarryOver = carry;
		return updateSumAndModifiedFields();
	}

	bool hasModified() const {
		return _modified;
	}

	void clearModified() {
		_modified = false;
	}

	int carry() const {
		return _carry;
	}

private: // functions
	bool changeBit(ullong &data, int bitIndex, int val) {
		if (val == 0)
			data = data & (~(1ull << bitIndex));
		else
			data = data | (1ull << bitIndex);

		return updateSumAndModifiedFields();
	}

	bool updateSumAndModifiedFields() {
		bool prevLastBit = _carry;
		_sum = _dataA + _dataB + _prevCarryOver;
		updateCarry();
		if(!_modified)
			_modified = (prevLastBit != _carry) ? true : false;
		else
			_modified = (prevLastBit != _carry) ? false : true;
		return _modified;
	}

	void updateCarry() {
		_carry = (1ull << 63) & _sum ? 1 : 0;
	}

	friend void unitTests();
	friend class TwoNBitBinaryNumbers;

private: // members
	ullong _dataA;
	ullong _dataB;
	ullong _sum;
	int _carry;
	bool _modified;
	int _prevCarryOver;
};


class TwoNBitBinaryNumbers
{
public:
	TwoNBitBinaryNumbers(const string &numA, const string &numB) 
		:_modified(false), N(numA.size()) {
		_NBit.clear();
		int nBitSize = N/BITSIZE;
		int residue = N%BITSIZE;
		int carry = 0;
		auto itA = numA.rbegin(), itB = numB.rbegin();
		for(int index = 0; index < nBitSize; ++index)
		{
			ullong A = binaryToULLong(itA, itA+BITSIZE);
			ullong B = binaryToULLong(itB, itB+BITSIZE);
		   	_NBit.push_back(LongLongSumData(A, B, carry));
			carry = _NBit[index].carry();
			itA = itA + BITSIZE;
			itB = itB + BITSIZE;
		}
		if(residue) 
		{
			ullong A = binaryToULLong(itA, numA.rend());
			ullong B = binaryToULLong(itB, numB.rend());
			_NBit.push_back(LongLongSumData(A, B, carry));
		}
	}

	const int sumIndex(int bitIndex)  {
		int index = bitIndex/BITSIZE;

		auto modIdxIT = modifiedIndexSet.begin();
		while(modIdxIT != modifiedIndexSet.end() && *modIdxIT <= index)
		{
			updateModified(*modIdxIT);
			modIdxIT = modifiedIndexSet.begin();
		}

		if( index >= _NBit.size())
			return _NBit[_NBit.size()-1].carry();
		return _NBit[index][bitIndex%BITSIZE];
	}

	const int operator[](int bitIndex)  {
		return sumIndex(bitIndex);
	}

	void changeBitA(int bitIndex, int val) {
		if(_NBit[bitIndex/BITSIZE].changeBitA(bitIndex%BITSIZE, val))
		{
			modifiedIndexSet.insert(bitIndex/BITSIZE);
		}
		else
		{
			modifiedIndexSet.erase(bitIndex/BITSIZE);
		}
	}

	void changeBitB(int bitIndex, int val) {
		if(_NBit[bitIndex/BITSIZE].changeBitB(bitIndex%BITSIZE, val))
		{
			modifiedIndexSet.insert(bitIndex/BITSIZE);
		}
		else
		{
			modifiedIndexSet.erase(bitIndex/BITSIZE);
		}
	}
private:
	void updateModified(int modifiedIndex) {
		int carry = _NBit[modifiedIndex].carry();
		_NBit[modifiedIndex].clearModified();
		modifiedIndexSet.erase(modifiedIndex);
		modifiedIndex++;

		bool modified = true;
		while( modified && modifiedIndex < N )
		{
			modified = _NBit[modifiedIndex].updateSum(carry);
			_NBit[modifiedIndex].clearModified();
			modifiedIndexSet.erase(modifiedIndex);
			modifiedIndex++;
		}
	}

	void print() {
		int index = 0;
		for(auto it = _NBit.begin(); it != _NBit.end(); ++it, ++index)
		{
			cout << "Part: " << index <<endl;
			cout << "A: " << ullongToString(it->_dataA) << endl;
			cout << "B: " << ullongToString(it->_dataB) << endl;
			cout << "S: " << ullongToString(it->_sum) << endl;
		}
	}

	vector<LongLongSumData> _NBit;
	ullong N;
	bool _modified;
	set<int> modifiedIndexSet;
	friend void unitTests();
};


int solveChangingBits()
{
	int N, Q;
	cin >> N >> Q;
	string A, B;
	cin >> A;
	cin >> B;

	TwoNBitBinaryNumbers twoSumNums(A, B);
	for(int query = 0; query < Q; ++query)
	{
		string q;
		cin >> q;
		if(q == "set_a")
		{
			int index, val;
			cin >> index >> val;
			twoSumNums.changeBitA(index, val);
		}
		else if (q == "set_b")
		{
			int index, val;
			cin >> index >> val;
			twoSumNums.changeBitB(index, val);
		}
		else if (q == "get_c")
		{
			int index;
			cin >> index;
			cout << twoSumNums[index];
		}
	}
}

void unitTests() 
{
	LongLongSumData sumNums(5ull, 1ull);
	assert(sumNums[5] == 0);
	assert(sumNums[0] == 0);
	sumNums.changeBitA(0, 0);
	assert(sumNums[0] == 1);
	assert(sumNums.changeBitB(0, 0) == 0);
	assert(sumNums[0] == 0);
	sumNums.updateSum(1);
	assert(sumNums[0] == 1);
	LongLongSumData sumNums1(-1ull + (1ull << 63), (1ull << 62));
	assert(sumNums1[63] == 1);
	assert(sumNums1[62] == 0);
	sumNums1.updateSum(1);
	assert(sumNums1[0] == 0);
	string num15("1111");
	assert(binaryToULLong(num15.rbegin(), num15.rend()) == 15ull);
	string num10("1010");
	assert(binaryToULLong(num10.rbegin(), num10.rend()) == 10ull);
	string numLarge("1111111111111111111111111111111111111111111111111111111111111111");
	assert(binaryToULLong(numLarge.rbegin(), numLarge.rend()) == -1ull);
	string num2n("0100000000000000000000000000000000000000000000000000000000000000");
	assert(binaryToULLong(num2n.rbegin(), num2n.rend()) == (1ull << 62));

	TwoNBitBinaryNumbers twoBinNums(numLarge, num2n);
	assert(twoBinNums._NBit.size() == 2/N_ULLS);
	assert(twoBinNums.N == 64);
	assert(twoBinNums[63] == 0);
	assert(twoBinNums[64] == 1);
	string doubleNumLarge("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	twoBinNums = TwoNBitBinaryNumbers(doubleNumLarge, doubleNumLarge);
	assert(twoBinNums._NBit.size() == 4/N_ULLS);
	assert(twoBinNums.N == 64*3);
	twoBinNums.changeBitB(62,0);
	assert(twoBinNums[62] == 0);
	twoBinNums.changeBitA(62,0);
	assert(twoBinNums[63] == 0);
//	twoBinNums.print();
	twoBinNums.changeBitB(64*3-2, 0);
//	twoBinNums.print();
	assert(twoBinNums[64*3-2] == 0);

	string doubleNumLarge2("111111111111111111111111111111111111111111111111111111111111111");
	twoBinNums = TwoNBitBinaryNumbers(doubleNumLarge2, doubleNumLarge2);
	assert(twoBinNums.N == 63);
	assert(twoBinNums._NBit.size() == 1/N_ULLS);
	assert(twoBinNums[63] == 1);
	assert(twoBinNums[62] == 1);
	twoBinNums.changeBitA(62, 0);
	assert(twoBinNums[62] == 0);

}

int main(int argc, char *argv[])
{
	unitTests();
//	solveChangingBits();
	return 0;
}
