#include <cstdio>

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

void printNSpaces(int n) {
	REP(i, 0, n) printf(" ");
}
void printNStars(int n) {
	REP(i, 0, n) printf("*");
}
void printNPipes(int n) {
	REP(i, 0, n) printf("|");
}
int main(int argc, char *argv[])
{
	int add = 3; // add 3 to given N
	int N;
	scanf("%d", &N);

	int nStars = 1; // start with 1 star
	int inc = 3;
	REP(curSet, 0, N) { // first find the number of stars in the last row
		if(curSet%2 == 0) nStars = 2*(inc-1) + nStars;
		else nStars = 2*(inc-2) + nStars;
		inc++;
	}
	int lastrow = N%2==0? nStars+4 : nStars+2;
	int spaces = lastrow/2;

	// enough info for printing spaces & stars
	inc = 3; nStars = 1;
	REP(curSet, 0, N) {
		printNSpaces(spaces);
		printNStars(nStars);
		printf("\n");
		nStars += 2;
		spaces--;
		REP(row, 0, inc) {
			printNSpaces(spaces);
			printNStars(nStars);
			nStars += 2;
			spaces--;
			printf("\n");
		}
		if(curSet%2 == 0) { nStars -= 4; spaces+=2; }
		else { nStars -= 6; spaces+=3;}
		inc++;
	}

	// print the pipes 
	int npipes = (N%2==0) ? N+1:N;
	spaces = (lastrow/2) - (npipes/2);
	REP(pipe, 0, N) {
		printNSpaces(spaces);
		printNPipes(npipes);
		printf("\n");
	}

	return 0;
}
