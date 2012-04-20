#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))
#define PII pair<int, int>
#define MAXBILLS 101
#define MAXMONEY 20001
PII memo[101][10010];
int bills[101];
int numOfCoins;

PII minMoneyCoins(int curBill, int curMoney)
{

	if(memo[curBill][curMoney].first != -1) return memo[curBill][curMoney];
	//printf("%d %d\n", curBill, curMoney);
	if(curMoney == 0) return memo[curBill][curMoney] = make_pair(0, 0);
	if(curBill == 1)
		if(bills[curBill] >= curMoney)
			return memo[curBill][curMoney] = 
				make_pair(bills[curBill] - curMoney, 1);
		else make_pair(MAXMONEY, MAXBILLS);
	else if(bills[curBill] <= curMoney)
	{
		PII res1 = minMoneyCoins(curBill-1, curMoney);
		PII res2 = minMoneyCoins(curBill-1, curMoney-bills[curBill]);
		res2.second += 1;
		return memo[curBill][curMoney] = min(res1, res2);
	}
	else return memo[curBill][curMoney] = 
			 min(make_pair(bills[curBill]-curMoney, 1), 
				 minMoneyCoins(curBill-1, curMoney));
}

void clearMemo(int b, int m)
{
	REP(bill, 0, b+1)
		REP(money, 0, m+1)
		memo[bill][money].first = -1;
}

int main(int argc, char *argv[])
{
	int n, money, nBills;
	scanf(" %d", &n);
	while(n--) {
		scanf(" %d %d", &money, &nBills);
		REP(bill, 1, nBills+1) scanf(" %d", &bills[bill]);
		clearMemo(nBills, money);
		PII res= minMoneyCoins(nBills, money);
		printf("%d %d\n", money+res.first, res.second);
	}
	return 0;
}

