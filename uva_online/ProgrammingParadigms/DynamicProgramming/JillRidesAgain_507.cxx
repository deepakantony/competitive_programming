#include <cstdio>

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

int main(int argc, char *argv[]) 
{
	int b, s, sum, k, l, temp, niceness, newst;
	scanf("%d", &b);
	REP(route, 1, b+1) {
		scanf(" %d", &s);
		// Find k, l such that sum[k:l] is maximum
		k = l = 0; temp = 0; newst = 0;
		sum = 0; // don't care for max sums that are -ve
		// can be -INF for including -ve cases
		REP(stop, 1, s) {
			scanf(" %d", &niceness);
			temp += niceness;
			if(temp > sum || (temp==sum && (stop-newst) > (l-k))) {
				k = newst + 1;
				l = stop+1;
				sum = temp;
			}
			else if(temp < 0) {
				temp = 0;
				newst = stop;
			}
		}
		if(sum == 0) printf("Route %d has no nice parts\n", route);
		else 
			printf(
				"The nicest part of route %d is between stops %d and %d\n",
				route, k, l);
	}
	return 0;
}
