#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <cctype>
#include <cstdlib>
#include <functional>
#include <numeric>

using namespace std;

string trainingData[4][50] = 
{
	{ 
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"APL*APPLE ONLINE STORE 800-676-2775 CA", 
		"AGILE WEB SOLUTIONS ST THOMAS CA",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"LATE FEE - AUG PAYMENT PAST DUE",
		"WOOT.COM SERVICE@WOOT.TX",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"PAYPAL *STEVENSACKS 402-935-7733 CA",
		"MI RANCHITO UNIVERSITY CYMO",
		"O'REILLY MEDIA SEBASTOPOL CA",
		"DREAMHOST.COM 877-829-4070 CA",
		"Panic *Transmit 4 PANIC.COM/CC OR",
		"LATE FEE - SEP PAYMENT PAST DUE",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"ADOBE SYSTEMS, INC. 800-833-6687 WA",
		"SIT4LESS.COM 703-3391300 MD",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"LYNDA.COM 805-477-3900 CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"GOOGLE *ALFRED APP GOOGLE.COM/CHGB",
		"Amazon.com AMZN.COM/BILLWA",
		"O'REILLY MEDIA SEBASTOPOL CA",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"PAYPAL *PRAGPROG BK 402-935-7733 TX",
		"INCASE DESIGNS CORP 626-338-6400 CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"LYNDA.COM 805-477-3900 CA",
		"O'REILLY MEDIA SEBASTOPOL CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"PAYPAL *SOFA BV 35314369001 NL",
		"LYNDA.COM 805-477-3900 CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"PP *FS ZENAWARE 402-935-7733 CA",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"PAYPAL *PMGWORLDWID 402-935-7733 NM",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"LYNDA.COM 805-477-3900 CA",
		"PAYPAL *COCOATECH 402-935-7733 CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"FOREIGN TRANSACTION FEE*INTEREST CHARGE",
		"2NDSITE FRESHBOOKS 416-481-6946 CA",
		"CLICK-TO-PAY PAYMENT, THANK YOU",
		"LYNDA.COM 805-477-3900 CA"
	},
	{
		"Click-to-pay",
		"Apple Online Store",
		"agilebits.com",
		"Credit Card Foreign Transaction Fee",
		"Late Fee",
		"Woot.com",
		"Freshbooks",
		"Steven Sacks",
		"Mi Ranchito",
		"O'Reilly Media",
		"DreamHost",
		"Panic.com",
		"Late Fee",
		"Credit Card Foreign Transaction Fee",
		"Freshbooks",
		"ICICI Bank Credit Card ",
		"Adobe",
		"Sit4Less.com",
		"Credit Card Foreign Transaction Fee",
		"Freshbooks",
		"Lynda.com",
		"ICICI Bank Credit Card ",
		"Alfred",
		"Amazon",
		"O'Reilly Media",
		"Credit Card Foreign Transaction Fee",
		"The Pragmatic Bookshelf",
		"Incase Designs",
		"ICICI Bank Credit Card ",
		"Freshbooks",
		"Lynda.com",
		"O'Reilly Media",
		"ICICI Bank Credit Card ",
		"Credit Card Foreign Transaction Fee",
		"Freshbooks",
		"Sofa BV",
		"Lynda.com",
		"ICICI Bank Credit Card ",
		"Zenware",
		"Credit Card Foreign Transaction Fee",
		"ICICI Bank Credit Card ",
		"PGM World Wide",
		"Freshbooks",
		"Lynda.com",
		"Cocoatech",
		"ICICI Bank Credit Card ",
		"Credit Card Foreign Transaction Fee",
		"Freshbooks",
		"ICICI Bank Credit Card ",
		"Lynda.com"
	},

	{
		"Credit Card, Payment",
		"Apple, Store",
		"agilebits.com, AGILE WEB SOLUTIONS, Software",
		"Credit Card, Fee",
		"Credit Card, Fee",
		"Webstore, Deals",
		"Freshbooks, Software Service",
		"Software, Technology, Design",
		"Restaurant",
		"O'Reilly Media, Technology",
		"DreamHost, Web Hosting",
		"Software",
		"Credit Card, Fee",
		"Credit Card, Fee",
		"Freshbooks, Software Service",
		"ICICI Bank, Credit Card ",
		"Software",
		"Office, Furniture",
		"Credit Card, Fee",
		"Freshbooks, Software Service",
		"Software, Training",
		"ICICI Bank, Credit Card ",
		"Alfred, App",
		"Amazon",
		"O'Reilly Media, Technology",
		"Credit Card, Fee",
		"Books",
		"Incase Designs, Accessories",
		"ICICI Bank, Credit Card ",
		"Freshbooks, Software Service",
		"Software, Training",
		"O'Reilly Media, Technology",
		"ICICI Bank, Credit Card ",
		"Credit Card, Fee",
		"Freshbooks, Software Service",
		"Software, Technology, Design",
		"Software, Training",
		"ICICI Bank, Credit Card ",
		"Software",
		"Credit Card, Fee",
		"ICICI Bank, Credit Card ",
		"Freight Forwarders",
		"Freshbooks, Software Service",
		"Software, Training",
		"Software",
		"ICICI Bank, Credit Card ",
		"Credit Card, Fee",
		"Freshbooks, Software Service",
		"ICICI Bank, Credit Card ",
		"Software, Training"
	},
	{
		"Credit Card Payment",
		"Other expenses",
		"Cost of Goods Sold",
		"Credit Card Payment",
		"Credit Card Payment",
		"Other expenses",
		"Other expenses",
		"Other expenses",
		"Meals & entertainment",
		"Other expenses",
		"Cost of Goods Sold",
		"Cost of Goods Sold",
		"Credit Card Payment",
		"Credit Card Payment",
		"Other expenses",
		"Credit Card Payment",
		"Other expenses",
		"Office Supplies",
		"Credit Card Payment",
		"Other expenses",
		"Other expenses",
		"Credit Card Payment",
		"Cost of Goods Sold",
		"Other expenses",
		"Other expenses",
		"Credit Card Payment",
		"Other expenses",
		"Supplies",
		"Credit Card Payment",
		"Other expenses",
		"Other expenses",
		"Other expenses",
		"Credit Card Payment",
		"Credit Card Payment",
		"Other expenses",
		"Other expenses",
		"Other expenses",
		"Credit Card Payment",
		"Other expenses",
		"Credit Card Payment",
		"Credit Card Payment",
		"Cost of Goods Sold",
		"Other expenses",
		"Other expenses",
		"Other expenses",
		"Credit Card Payment",
		"Credit Card Payment",
		"Other expenses",
		"Credit Card Payment",
		"Other expenses"
	}
};

#define VS vector<string>
#define M_S_VS map<string, VS > 
#define S_ITER string::iterator
#define FOREACH(it, ctnr) for(__typeof__(ctnr.begin()) it = ctnr.begin(); \
							  it != ctnr.end(); ++it)
#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

void initCategories(set<string> catSet) 
{

}

VS splitToWords(string s)
{

}

string capitalize(string s)
{
	string res(s.length(), 0);
	transform(s.begin(), s.end(), res.begin(), ptr_fun<int,int>(tolower));
	S_ITER it = res.begin();
	while(it != res.end()) {
		*it = toupper(*it);
		it = find_if(it, res.end(), not1(ptr_fun<int,int>(isalpha)));
		it = find_if(it, res.end(), ptr_fun<int,int>(isalpha));
	}
	return res;
}

string cleanWord(string s)
{
	string res1 = capitalize(s);
	string res(res1.length(), 0);
	REP(i, 0, res1.length()) {
		if(isalpha(res1[i]) || isspace(res1[i]))
			res[i] = res1[i];
		else if(res1[i] == '*')
			res[i] = ' ';
		res[i+1] = 0;
	}
	return res;
}

string commaAdd(string s)
{
	string res(s.length(), 0);
	REP(i, 0, s.length()) {
		if(isspace(s[i]))
			res[i] = ',';
		else res[i] = s[i];
	}
	return res;
}

string categorize(string s)
{
	return string("Uncategorized");
}


void simpleDataCleaning()
{
	VS opname, optags, opcats;
	M_S_VS directMapping;
	for(int i = 0; i < 50; i++) {
		VS opVec;
		opVec.push_back(trainingData[1][i]);
		opVec.push_back(trainingData[2][i]);
		opVec.push_back(trainingData[3][i]);
		directMapping[trainingData[0][i]] = opVec;
	}
	FOREACH(it, directMapping)
		cout << cleanWord(it->first) << ": " 
			 << it->second[0] << " | " 
			 << it->second[1] << " | "
			 << it->second[2] << endl;

	int N; string input;
	M_S_VS::iterator it;
	cin >> N;
	while(N--) {
		cin >> input;
		if((it=directMapping.find(input)) != directMapping.end()) {
			
			opname.push_back(it->second[0]);
			optags.push_back(it->second[1]);
			opcats.push_back(it->second[2]);
		}
		else {
			opname.push_back(cleanWord(input));
			optags.push_back(commaAdd(cleanWord(input)));
			optags.push_back(categorize(cleanWord(input)));
		}
	}

	FOREACH(it, opname)
		cout << *it << endl;
	FOREACH(it, optags)
		cout << *it << endl;
	FOREACH(it, opcats)
		cout << *it << endl;
}

int main(int argc, char *argv[]) 
{
	simpleDataCleaning();
	return 0;
}
