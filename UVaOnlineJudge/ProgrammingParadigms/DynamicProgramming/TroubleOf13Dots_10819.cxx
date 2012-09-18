// Problem F: Trouble of 13-Dots
// 
// Time limit: 2 seconds
// 
// Do you know 13-Dots? She is the main character of a well-known Hong Kong 
// comic series. She is famous of her beauty, as well as the variety of stylish 
// clothes she wears. Here are some pictures of 13-Dots that I found on the Web:
// 
//   
// 
// Now 13-Dots is facing a problem. She used to have a large amount of pocket 
// money every month. However, her father has decided to cut down her budget of 
// buying new clothes! In the past, she would buy every dress she liked without
//  hesitation, but now she needs careful consideration before making any 
// purchase. Every month, she prepares a list containing the prices and 'favour 
// indices' (ranging from 1 to 5) of all items she is interested. At the end of 
// the month, she would decide how to spend her money such that the total favour 
// value is maximized. It is important to know that 13-Dots always uses her 
// credit card to pay the bill, which offers her a 200-dollar refund if her 
// total expense in the month exceeds $2000. For example, if her budget is 
// $5000, she can buy clothes with total marked price of at most 5200 dollars.
// 
// Since the optimal way is hard to be figured out just by hand, can you write 
// a program for 13-Dots that helps her make the decision? Remember that you 
// should NEVER select an item more than once, even if this leads to a greater 
// total favour value.
// 
// Input
// 
// The input consists of several test cases. Each of them has the following 
// format:
// 
// The first line gives two integers, m and n (0 ≤ m ≤ 10000, 0 ≤ n ≤ 100), 
// which are the amount of pocket money 13-Dots has and the number of items 
// on the list respectively. The following n lines each contains two integers,
//  p and f (0 < p ≤ 4000, 1 ≤ f ≤ 5), where p is the marked price of the item, 
// and f is its 'favour index'.
// 
// Input is terminated by EOF.
// 
// Output
// 
// For each test case, print one line giving the maximum total favour value 
// 13-Dots can get.
// 
// Sample Input
// 
// 500 4
// 100 2
// 100 3
// 200 3
// 400 4
// Sample Output
// 
// 8
// Question 4 in OIPC, Nov. 2003
// Image sources include: http://www.hkcomics.com, http://www.yesasia.com, http://isubculture.ichannel.com.hk

#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(i,st,n) for(int (i) = (st); (i) < (n); ++(i))
#define PII pair<int,int>
#define MP make_pair

int price[101], favIndex[101];
int origPM;
PII memo[101][10001];

PII add(int a, PII b) {
	return MP(a+b.first, b.second);
}

PII mostFav(int item, int pocketMoney)
{
	if(memo[item][pocketMoney].first != -1)return memo[item][pocketMoney];

	if(origPM <= 2000) {
		if(item == 0) 
			return memo[item][pocketMoney] = MP(0, origPM-pocketMoney) ;
		if(pocketMoney >= price[item]) {
			PII inc = add(favIndex[item],mostFav(item-1, pocketMoney-price[item]));
			PII notinc = mostFav(item-1, pocketMoney);
			return memo[item][pocketMoney] = max(inc, notinc);
		}
		else return memo[item][pocketMoney] = mostFav(item-1, pocketMoney);
	}
	else {
		if(item == 0) 
			return memo[item][pocketMoney] = MP(0, origPM-pocketMoney) ;
		if(pocketMoney >= price[item]) {
			PII inc = add(favIndex[item],mostFav(item-1, pocketMoney-price[item]));
			PII notinc = mostFav(item-1, pocketMoney);
			//if( inc.second > 2000)
			return memo[item][pocketMoney] = max(inc, notinc);
				//else return memo[item][pocketMoney] = notinc;
		}
		else return memo[item][pocketMoney] = mostFav(item-1, pocketMoney);
	}
}

void clearMemo()
{
	REP(i, 0, 101) REP(j, 0, 10001) {
		memo[i][j] = MP(-1,-1);
	}
}

int main(int argc, char *argv[])
{
	int n;
	while(scanf(" %d %d", &origPM, &n)!=EOF) {
		REP(i, 1, n+1) 
			scanf(" %d %d", &price[i], &favIndex[i]);
		clearMemo();
		PII res;
		if(origPM > 1800) {
			origPM = origPM+200;
			res = mostFav(n, origPM);
			if(res.second <= 2000) {
				origPM -= 200;
				res = mostFav(n, origPM);
			}
		}
		else
			res = mostFav(n, origPM);
		printf("%d\n", res.first);
	}
	return 0;
}
