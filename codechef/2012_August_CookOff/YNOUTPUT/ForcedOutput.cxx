//http://www.codechef.com/problems/YNOUTPUT/

#include <cstdio>

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

int input[100][100];
int T;

bool match(int test1, int test2)
{
	REP(i, T)
		if(input[test1][i] != input[test2][i])
			return false;
	return true;
}

int main(int argc, char *argv[])
{
	int output[100];
	scanf("%d", &T);
	char inpChar[5];
	REP(test, T) REP(line, T)
		scanf("%s", inpChar), input[test][line] = inpChar[0] == 'N' ? 0 : 1;
	REP(test, T)
		if(input[test][test] == 0)
			output[test] = 0;
		else {
			output[test] = 1;
			// no yes before this test
			REP(i, test)
				if(input[test][i] != 0) {
					output[test] = 0; break;
				}

			if(output[test] == 1) {
				FOR(i, test+1, T) {
					if(input[test][i] == 0) {
						if(match(i, test)) {
							output[test] = 0; break;
						}
					}
					else if(input[test][i] == 1) {
						if(!match(i, test)) {
							output[test] = 0; break;
						}
					}
				}
			}
			if(output[test] == 1) {
				REP(i, T)
					if(input[test][i] == 0)
						printf("NO\n");
					else
						printf("YES\n");
				return 0;
			}
		}
	
	REP(i, T) printf("NO\n");
	return 0;
}



