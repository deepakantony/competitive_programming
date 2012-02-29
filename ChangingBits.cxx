#include <iostream>
#include <string>
#include <cassert>

using namespace std;


typedef unsigned long long ullong;

template<class iterator_type>
ullong binaryToULLong(iterator_type begin, iterator_type end)
{
	ullong res = 0;
	int index = 0;
	for(iterator_type it = begin; it != end; ++it, ++index)
		if(*it == '1')
			res |= (1 << index);

	if(index > 64)
		throw "More than 63 bits getting extracted.";

	return res;
			
}

class LongLongSumData
{
public:
	LongLongSumData(ullong dataA, ullong dataB) 
		: _dataA(dataA), _dataB(dataB), _modified(false) {}

	const int& operator[](int bitIndex) const {
		if ( _dataA & ( 1 << bitIndex ) > 0 )
			return 1;
	}

	bool hasChanged() const {
		return _modified;
	}

	bool changeBitA(int bitIndex, int val) {
		return changeBit(_dataA, bitIndex, val);
	}

	bool changeBitB(int bitIndex, int val) {
		return changeBit(_dataB, bitIndex, val);
	}

	void updateSum() {
		_sum = _dataA + _dataB;
		updateCarry();
		_modified = false;
	}

	int carry() {
		reutn _carry;
	}

private: // functions
	bool changeBit(ullong &data, int bitIndex, int val) {
		if (val == 0)
			data = data & (~(1ull << bitIndex));
		else
			data = data | (1ull << bitIndex);

		return updateSumAndModifiedFields();
	}

	bool updateSumAndModifiedFields(int carry = 0) {
		bool prevLastBit = _carry;
		_sum = _dataA + _dataB;
		updateCarry();
		if(!_modified)
			_modified = (prevLastBit != curLastBit) ? true : false;
		return _modified;
	}

	void updateCarry() {
		_carry = (1ull << 63) & _sum ? true : false;
	}

	ullong binaryToULLong(const string &binary, int fromIndex, int nextIndex) {
		
	}

private: // members
	ullong _dataA;
	ullong _dataB;
	ullong _sum;
	int _carry;
	bool _modified;
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
			_NBit.push_back(LongLongData(A, B));
		}
	}

	int sumIndex(int bitIndex) {
		
	}
private:
	vector<LongLongData> _NBit;
	bool _modified;
};



void unitTestsLongLongDataSum() 
{
	LongLongDataSum sumNums(5, 1);
	assert(sumNums[5] == 0);
	assert(sumNums[0] == 0);
	sumNums.changeBitA(0, 0);
	assert(sumNums[0] == 1);
	sumNums.changeBitB(0, 0);
	assert(sumNums[0] == 0);
}

int main(int argc, char *argv[])
{
	
	return 0;
}
