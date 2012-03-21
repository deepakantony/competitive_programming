#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> temp;
	int *t = new int[100000*100000];
	for(int i = 0; i < 100000*10000; ++i)
		t[i] = 0;
	cout << temp.max_size() << endl;
}
