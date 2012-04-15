#include <cstdio>

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))


int main(int argc, char *argv[])
{
	int a[150][150];
	int N, N2;

	int newst, k, l, prefix[150], temp, x1,y1,x2,y2;
	int stIdx[150];

	int nTests; scanf(" %d", &nTests);

	while(nTests--)
	{
		scanf(" %d", &N);
		N2 = 2*N-2; if(!N2) N2 = N;
		REP(i, 0, N) REP(j, 0, N) 
		{ 
			scanf(" %d", &a[i][j]); 
			a[N+i][j] = a[i][N+j] = a[i+N][j+N] = a[i][j];
		}
		int maxSum = -100*150*150; // -INF - for this prob
		REP(row, 0, N) 
		{
			REP(col, 0, N2) prefix[col] = 0;

			REP(row2, row, N2) 
			{
				newst = temp = k = l = 0; 

				if(row2 >= N && row <= (row2-(N-1))) break;
				REP(col, 0, N) 
				{
					if(col >= N) {
						if(col == N && newst == 0)
						{ newst = 2; temp -= (prefix[0] + prefix[1]); }
						else if(newst <= col-(N-1))
						{ newst = col-(N-2); temp -= prefix[col-(N-1)]; }
						if(temp < 0) { temp = 0; newst = col; }
					}
					prefix[col] += a[row2][col];
					temp += prefix[col];
					if(temp > maxSum) {
						maxSum = temp;
						x1 = row+1; x2 = row2+1;
						y1 = k = newst+1; 
						y2 = l = col+1; 
					}
					if(temp < 0) {
						temp = 0;
						newst = col + 1;
					}
				}
				memset(stIdx, 0, sizeof stIdx);
				newst = 0;
				for(int col = N-1; col >= 0; col--)
					if(prefix[col] 

				REP(col, N, N+N-2)
				{
					
				}
			}
		}
		printf("%d\n", maxSum);
		printf("%d (%d %d) (%d %d)\n", maxSum, x1, y1, x2, y2);
	}

	return 0;
}
