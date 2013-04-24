#include <cstdio>
#include <cstring>

char bag[101];
int nBags;

void punch(int i)
{
	bag[i] = '0';
	if(i>0 && bag[i-1] != '0') bag[i-1]--;
	if(i<(nBags-1) && bag[i+1] != '0') bag[i+1]--;
	//printf("%s after punching %d\n", bag, i+1);
}

int numPunches() 
{
	int nPunches = 0;

	for(int i = 0; i < nBags-1; ++i) {
		if(bag[i] == '0') continue;
		if(bag[i+1] == '0' || bag[i] == '1' || bag[i+1] > bag[i]) { 
			punch(i); nPunches++; continue;
		}
		int j = i+1; 
		while(j < nBags && (bag[j] == '2' || bag[j] == '3')) j++;
		if(j == nBags) j--;
		while(j >= i) {
			if(bag[j] != '0') {
				punch(j); nPunches++;
			}
			j--;
		}				
	}
	if(bag[nBags-1] != '0') { punch(nBags-1); nPunches++; }
		
	return nPunches;
}

int main(int argc, char *argv[])
{
	scanf("%s", bag);
	nBags = strlen(bag);
	printf("%d\n", numPunches());
	return 0;
}
