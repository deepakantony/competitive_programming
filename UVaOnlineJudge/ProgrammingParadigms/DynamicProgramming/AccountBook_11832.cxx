//   Account Book 
// The FCC (Foundation for Combating Corruption) dismantled a major corruption 
// scheme in Nlogonia. During the operation, several account books, with notes 
// documenting the illicit transactions carried out by the scheme, were seized 
// by FCC agents.
// Each page on the account books contains some transactions (income or expense, 
// in nilogos, the local currency of Nlogônia, whose symbol is N$) and the cash 
// flow resulting from transaco tions on that page. For example, if a page 
// recorded the following transactions: an income of N$ 7, an income of N$ 2, 
// an expense of N$ 3, an income of N$ 1 and an expense of N$ 11, the cash flow 
// on that page would be 7 + 2 - 3 + 1 - 11 = -4.
// 
// However, to obstruct the work of the police, the offenders did not record
//  in their account books the type of each transaction (income or expense). 
// In the example above, the page would contain only the numbers 7, 2, 3, 1 
// and 11 (with no indication whether they were income or expense 
// transactions). The cash flow for each page, however, was always recorded 
// normally, with the signal (in this case, -4).
// 
// To guarantee that the offenders are convicted, prosecutors must be able to 
// determine with certainty whether each transaction is an income or an 
// expense. In the example above, transaction N$ 7 was certainly an income, 
// and transaction N$ 11 was certainly an expense. But we cannot say anything 
// about transactions N$ 2, N$ 3, and N$ 1. Transactions N$ 2 and N$ 1 could 
// have been income and in this case transaction N$ 3 would have been an 
// expense; or N$ 1 and N$ 2 could have been expenses and in this case 
// transaction N$ 3 would be an income.
// 
// Many account books have a relatively large number of pages, with many 
// transactions, making it is difficult for the police to process all the 
// information. Therefore, they need a program that performs the task
//  efficiently.
// 
// Input 
// 
// The input consists of several test cases. The first line of a test case 
// contains two integers N and F, indicating the number of transactions on 
// the page ( 2N40) and cash flow for this page ( -16000F16000). Each of the 
// following N lines contains an integer Ti indicating the value of the i-th 
// transaction ( 1Ti1000).
// The last test case is followed by a line containing only two numbers zero 
// separated by a space.
// 
// Output 
// 
// For each test case the input your program must print a single line with N 
// characters. The i-th character must be `+', if it is possible determine 
// with certainty that the i-th transaction is an income, `-', if it is 
// possible to determine with certainty that the i-th operation is an expense, 
// and `?', if it is impossible to determine with certainty the type of 
// transaction. If the cash flow recorded in the page cannot be obtained from 
// the transactions recorded in the page, your program must print a single 
// line containing the character `*'.
// Sample Input 
// 
// 5 7
// 1
// 2
// 3
// 4
// 5
// 4 15
// 3
// 5
// 7
// 11
// 5 12
// 6
// 7
// 7
// 1
// 7
// 0 0
// Sample Output 
// 
// ?+??+
// *
// +??-?
// 

#include <cstdio>
#include <cstring>

int memo[120000][41];
char finalAns[41];
int transaction[41];

void printFinalAns(int size) {
	for(int i = 1; i <= size; i++)
		printf("%c", finalAns[i]);
	printf("\n");
}
	
int gi(int i) { return i>=0?i: 120000+i; }
int getMemo(int item, int flow) {
	return memo[gi(flow)][item];
}

int updateFinalAns(bool flowPlus, bool flowMinus, int item)
{
	int res = 0;
	if(flowPlus) { 
		res = 1; 
		if(finalAns[item] == 0 ) finalAns[item] = '+'; 
		else if(finalAns[item] != '+')  finalAns[item] = '?';
	}
	if(flowMinus) { 
		res = 1; 
		if(finalAns[item] == 0) finalAns[item] = '-';
		else if(finalAns[item] != '-') finalAns[item] = '?';
	}
	return res;
}

int accountBook(int item, int flow) {
	if(getMemo(item,flow) != -1) return getMemo(item,flow);
	int res;
//	printf("Enter: %d %d :", item, flow); printFinalAns(item);
	if(item == 1)
		res = memo[gi(flow)][item] = updateFinalAns( 
			(flow-transaction[item]) == 0, (flow+transaction[item]) == 0, item);
	else
		res =  memo[gi(flow)][item] = updateFinalAns(
			accountBook(item-1, flow-transaction[item]) == 1,
			accountBook(item-1, flow+transaction[item]) == 1, item);
//	printf("Exit: %d %d :", item, flow); printFinalAns(item);
	return res;
}

int main(int argc, char *argv[])
{
	int N, F;
	for(scanf(" %d %d", &N, &F);N!=0; 
		scanf(" %d %d", &N, &F)) 
	{
		for(int i = 1; i <= N; i++)
			scanf(" %d", &transaction[i]);
		memset(memo, -1, sizeof memo);
		memset(finalAns, 0, sizeof finalAns);
		if(accountBook(N, F))
			printFinalAns(N);
		else printf("*\n");

	}
	
	return 0;
}
