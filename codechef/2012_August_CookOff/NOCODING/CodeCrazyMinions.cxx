#include <cstdio>
#include <cstring>
#include <cassert>

int main(int argc, char *argv[]) {
	int T; scanf("%d", &T);
	char word[1001];

	while(T--) {
		scanf("%s", word);
		int len = strlen(word);
		assert(len>0);
		int codelength = 2; // 1st load instruction and print
		char cur;
		char prev = word[0];
		for(int i = 1; word[i]; ++i) {
			cur = word[i];
			// for increment
			int inc = (cur>=prev ? cur-prev : 'z' + cur - prev - 'a' + 1);
			//fprintf(stderr, "%d %d %d\n", inc, 'z'-cur, prev-'a');
			codelength += inc;
			codelength++; // for print
			prev = cur;
		}
		//fprintf(stderr, "%s %d\n",word, codelength);
		if(codelength > len*11)
			printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
		
