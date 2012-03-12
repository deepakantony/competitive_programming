#include <iostream>
#include <string>
#include <cassert>

using namespace std;

typedef unsigned short ushort;

ushort flipShort(ushort n)
{
	return (~n) & (0xFFFF >> 1);
}

ushort flipBit(ushort n, int bitPosition)
{
	return ((~n) & (1<<bitPosition)) | ((n) & (~(1<<bitPosition)));
}

string decToBinary(ushort n)
{
	string binary;
	while(n > 0)
	{
		binary += '0'+n%2;
		n /= 2;
	}
	while(binary.size() < 16)
		binary += '0';
	reverse(binary.begin(), binary.end());
	return binary;
}




void unitTest()
{
	// flipShort function
	ushort ten = 10, three = 3, two =2, four = 4;
	assert(flipShort((ushort)10) != ~ten);
	assert(flipShort(10) == (~ten & (0x7FFF)));
	assert(flipShort(three) == (ushort)32764);

	// flipBit function
	assert(flipBit(4, 3) == (ushort)12);
	assert(flipBit(0, 10) == (ushort)(1<<10));

	// decToBinary functionxs
	assert(decToBinary(2) == string("0000000000000010"));
	assert(decToBinary(32764) == string("0111111111111100"));
}

int main(int argc, char *argv[])
{
	unitTest();
	return 0;
}
			
