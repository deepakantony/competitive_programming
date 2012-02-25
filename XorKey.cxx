#include <iostream>
#include <string>

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

int main(int argc, char *argv[])
{
	ushort N;
	cin >> N;
	cout << "N: " << decToBinary(N) << endl;
	cout << "N flipped: " << flipShort(N) << " is: " 
		 << decToBinary(flipShort(N)) << endl;
	cout << "N flip bit 3: " << flipBit(N, 3) << " is: " 
		 << decToBinary(flipBit(N,3)) << endl;
	cout << decToBinary((~N) & (1<<3)) << endl;
	cout << decToBinary(N & (~(1<<3))) << endl;
	return 0;
}
			
