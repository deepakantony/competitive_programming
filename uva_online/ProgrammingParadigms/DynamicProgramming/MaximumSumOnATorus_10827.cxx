#include <cstdio>


#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))


int main(int argc, char *argv[])
{
	int a[75][75];
	int N;

	int newst, k, l, prefix[75], tempmin, tempmax, maxSum, minSum, rowTotal;
	int stIdx[150];

	int nTests; scanf(" %d", &nTests);

	while(nTests--)
	{
		scanf(" %d", &N);

		REP(i, 0, N) REP(j, 0, N) 
			scanf(" %d", &a[i][j]); 

		maxSum = -101*75*75; // -INF - for this prob
		
		REP(row, 0, N) 
		{
			REP(col, 0, N) prefix[col] = 0;

			REP(row2, row, N) 
			{
				rowTotal = tempmax = tempmin = 0; 
				minSum = 101*75*75;
				REP(col, 0, N) 
				{
					prefix[col] += a[row2][col];

					tempmax += prefix[col];
					if(tempmax > maxSum) maxSum = tempmax;
					if(tempmax < 0)	tempmax = 0;

					tempmin += prefix[col];
					if(tempmin < minSum) minSum = tempmin;
					if(tempmin > 0) tempmin = 0;

					rowTotal += prefix[col];						
				}
				if((rowTotal-minSum) > maxSum && maxSum > 0) maxSum = rowTotal-minSum;
			}
		}
		int colTotal;
		REP(col, 0, N) 
		{
			REP(row, 0, N) prefix[row] = 0;
			REP(col2, col, N)
			{
				colTotal = tempmax = tempmin = 0;
				minSum = 101*75*75;
				REP(row, 0, N)
				{
					prefix[row] += a[row][col2];

					tempmax += prefix[row];
					if(tempmax > maxSum) maxSum = tempmax;
					if(tempmax < 0) tempmax = 0;

					tempmin += prefix[row];
					if(tempmin < minSum) minSum = tempmin;
					if(tempmin > 0) tempmin = 0;

					colTotal += prefix[row];
				}
				if((colTotal-minSum) > maxSum && maxSum > 0) maxSum = colTotal-minSum;
			}
		}
		printf("%d\n", maxSum);

	}

	return 0;
}
