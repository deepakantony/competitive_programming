// Problem C: Exact Change
// 
// Seller: That will be fourteen dollars.
// Buyer: Here's a twenty.
// Seller: Sorry, I don't have any change.
// Buyer: OK, here's a ten and a five. Keep the change.
// When travelling to remote locations, it is often helpful to bring cash, in 
// case you want to buy something from someone who does not accept credit or 
// debit cards. It is also helpful to bring a variety of denominations in case 
// the seller does not have change. Even so, you may not have the exact amount,
//  and will have to pay a little bit more than full price. The same problem can 
// arise even in urban locations, for example with vending machines that do not 
// return change.
// Of course, you would like to minimize the amount you pay (though you must pay 
// at least as much as the value of the item). Moreover, while paying the 
// minimum amount, you would like to minimize the number of coins or bills that 
// you pay out.
// 
// 
// Input Specification
// 
// The first line of input contains one integer specifying the number of test
//  cases to follow. Each test case begins with a line containing an integer, 
// the price in cents of the item you would like to buy. The price will not 
// exceed 10 000 cents (i.e., $100). The following line contains a single 
// integer n, the number of bills and coins that you have. The number n is at 
// most 100. The following n lines each contain one integer, the value in cents 
// of each bill or coin that you have. Note that the denominations can be any 
// number of cents; they are not limited to the values of coins and bills that 
// we usually use in Canada. However, no bill or coin will have a value greater 
// than 10 000 cents ($100). The total value of your bills and coins will 
// always be equal to or greater than the price of the item.
// Sample Input
// 
// 1
// 1400
// 3
// 500
// 1000
// 2000
// Output Specification
// 
// For each test case, output a single line containing two integers: the total 
// amount paid (in cents), and the total number of coins and bills used.
// Output for Sample Input
// 
// 1500 2
// Ondřej Lhoták

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
		else return make_pair(MAXMONEY, MAXBILLS);
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

