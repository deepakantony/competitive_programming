#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

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
		: _dataA(dataA), _dataB(dataB), _sum(dataA+dataB), 
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

	int carry() {
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
		return _modified;
	}

	void updateCarry() {
		_carry = (1ull << 63) & _sum ? true : false;
	}

	friend void unitTests();

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
		:_modified(false) {
		_NBit.clear();
		for(auto itA = numA.rbegin(), itB = numB.rbegin(); 
			itA != numB.rend() && itB != numB.rend();
			itA += 63, itB += 63)
		{
			ullong A = binaryToULLong(itA, itA+63);
			ullong B = binaryToULLong(itB, itB+63);
			_NBit.push_back(LongLongSumData(A, B));
		}
	}

	int sumIndex(int bitIndex) {
		
	}
private:
	vector<LongLongSumData> _NBit;
	bool _modified;
};



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
}

int main(int argc, char *argv[])
{
	unitTests();
	return 0;
}
