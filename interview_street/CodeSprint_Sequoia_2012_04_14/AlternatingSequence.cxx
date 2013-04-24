#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int a[200000];
int N;
int temp[200000];

// longest alternate sequence
int las() 
{
	int curIndex = 0;
	temp[0] = a[0];
	bool greater = true;
	for(int i = 1; i < N; ++i)
		if(greater)
			if(a[i] > temp[curIndex])
			{ temp[++curIndex] = a[i]; greater = false; }
			else temp[curIndex] = a[i];
		else // lesser
			if(a[i] < temp[curIndex])
			{temp[++curIndex] = a[i]; greater = true; }
			else temp[curIndex] = a[i];
	return curIndex+1;
	
}

int main(int argc, char *argv[])
{
	scanf(" %d", &N);
	for(int i = 0; i < N; ++i)
		scanf(" %d", &a[i]);

	printf("%d\n", las());
}


