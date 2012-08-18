#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> count(1000001, 0);
	int N; scanf("%d", &N);
	int val;
	while(N--) scanf("%d", &val), ++count[val];
	for(int i = 0; i < 1000001; ++i)
		for(int j = 0; j < count[i]; ++j)
			printf("%d\n", i);
	return 0;
}
