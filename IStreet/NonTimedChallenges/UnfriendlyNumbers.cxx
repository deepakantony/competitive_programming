#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
	clock_t start = clock();
	int j = 0;
	for(int i = 0; i < 1000000000; i++)
		j = i%(i+1);

	clock_t end = clock();
	printf("%.2fs\n", (double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
