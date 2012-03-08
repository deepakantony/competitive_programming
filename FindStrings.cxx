#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdio>
#include <cstring>

using namespace std;

class SuffixArray
{
public:
	SuffixArray(); // default initialization for adding strings later
	SuffixArray(char *inpStr); // init with a string

	void add(char *inpStr);
	void updateVector();
	void updateSubstringVec();
	string substring(long long idx);
	string substringBinSearch(long long idx);
	void print() const;
	void printSubstrings() const;
private:
	void updateSuffixArray(char *inpStr);

	struct SANode 
	{
		SANode() 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0){}
/*		SANode(vector<string> *sl) 
		: leftIndex(-1), strIdx(-1), lcp(0), index(0) {}*/
		int strIdx; // string index
		int leftIndex; // starting position of the suffix
		int lcp; // longest common prefix
		long long index; // when queried this will be used to do the binary search
	};

	int findLCP(const SANode &prev, const SANode &cur) const;
	bool nodeHasStringIndex(const SANode &node, long long idx) const;
	bool nodeIsLTIndex(const SANode &node, long long idx) const;
	string constructStringInNode(const SANode &node, int prefixIndex) const;

	struct NodeCmp
	{
		NodeCmp(vector<char*> &sl, vector<int> &sll) : stringList(sl), stringLenList(sll){}
		bool operator() (const SANode &ths, const SANode &other) const; // this will be used by set for sorting	
		vector<char*> &stringList;
		vector<int> &stringLenList;
	} nc;
	void printNode(const SANode &node) const;

	set<SANode,NodeCmp> suffixSet; // this eliminates duplicates
	vector<SANode> suffixVec; // random access
	long long substringsMaxIndex; // number of distinct substrings - 1
	vector<char*> stringList; // list of strings and suffixs
	vector<int> stringLenList;

	struct SNode // substring node
	{
		SNode(int idx, int l, int r) : strIdx(idx), left(l), right(r) {}
		int strIdx;
		int left, right;
	};
	string constructSubstring(const SNode &node) const;
	void addAllSubstrings(const SANode &node);
	vector<SNode> substringVec;
};

SuffixArray::SuffixArray()
	: nc(stringList, stringLenList), suffixSet(nc)
{
}

SuffixArray::SuffixArray(char *inpStr)
	: nc(stringList, stringLenList), suffixSet(nc)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::add(char *inpStr)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::updateVector()
{
	suffixVec.clear();
	if(suffixSet.empty())
		return;

	// add it to the vector
	suffixVec.push_back(*suffixSet.begin());
	auto it = suffixSet.begin();
	SANode prev = *it;
	SANode cur;
	++it;
	while(it != suffixSet.end())
	{
		cur = *it;
		cur.lcp = findLCP(prev, cur);
		cur.index = 0ll + prev.index + stringLenList[prev.strIdx] - 
			(prev.lcp + prev.leftIndex);
		suffixVec.push_back(cur);

		prev = cur;
		++it;
	}
	substringsMaxIndex = 0ll + prev.index + stringLenList[prev.strIdx] - 
			(prev.lcp + prev.leftIndex) - 1ll;
}

void SuffixArray::updateSubstringVec()
{
	substringVec.clear();
	if(suffixSet.empty())
		return;
	addAllSubstrings(*suffixSet.begin());
	auto it = suffixSet.begin();
	SANode prev = *it;
	SANode cur;
	++it;
	while(it != suffixSet.end())
	{
		cur = *it;
		cur.lcp = findLCP(prev, cur);
		cur.index = 0ll + prev.index + stringLenList[prev.strIdx] - 
			(prev.lcp + prev.leftIndex);
		addAllSubstrings(cur);

		prev = cur;
		++it;
	}
}

void SuffixArray::addAllSubstrings(const SANode &node)
{
	for(int rightIndex = node.leftIndex + node.lcp + 1;
		rightIndex <= stringLenList[node.strIdx]; ++rightIndex)
		substringVec.push_back(SNode(node.strIdx, node.leftIndex, rightIndex));
}

string SuffixArray::substring(long long idx)
{
	if(idx < 0 || idx >= substringVec.size())
		return string("INVALID");
	return constructSubstring(substringVec[idx]);
}

string SuffixArray::constructSubstring(const SNode &subNode) const
{
	string res;
	for(auto it = stringList[subNode.strIdx] + subNode.left;
		it != stringList[subNode.strIdx] + subNode.right; ++it)
		res += *it;
	return res;
}

string SuffixArray::substringBinSearch(long long idx)
{
	if(idx < 0 || idx > substringsMaxIndex)
		return string("INVALID");

	string res;
	// binary search the suffixVec for the substring[idx]
	long long left = 0;
	long long right = suffixVec.size();
	long long middle = left + (right - left)/2;
	while(left < right)
	{
		if(nodeHasStringIndex(suffixVec[middle], idx))
		{
			int prefixIndex = idx - suffixVec[middle].index + 
				suffixVec[middle].leftIndex + suffixVec[middle].lcp + 1;
			//cout << prefixIndex << endl;
			res = constructStringInNode(suffixVec[middle], prefixIndex);
			break;
		}
		else if (nodeIsLTIndex(suffixVec[middle], idx))
		{
			left = middle + 1;
		}
		else 
		{
			right = middle;
		}
		middle = left + (right - left)/2;
	}
	return res.size() > 0 ? res : string("INVALID");
}

void SuffixArray::print() const
{
	for(auto it = suffixVec.begin(); it != suffixVec.end(); ++it)
		printNode(*it);
}

void SuffixArray::printSubstrings() const
{
	for(auto it = substringVec.begin(); it != substringVec.end(); ++it)
		cout << constructSubstring(*it) << endl;
}

void SuffixArray::updateSuffixArray(char *inpStr)
{
	int curIndex = stringList.size();
	stringList.push_back(inpStr);
	int strLen = strlen(inpStr);
	stringLenList.push_back(strLen);
	for(int leftIndex = 0; leftIndex < strLen; ++leftIndex)
	{
		SANode newNode;
		newNode.strIdx = curIndex;
		newNode.leftIndex = leftIndex;
		suffixSet.insert(newNode);
	}
}

int SuffixArray::findLCP(const SANode &prev, const SANode &cur) const
{
	int LCP = 0;
	for(auto it_this = stringList[prev.strIdx]+prev.leftIndex,
			it_other = stringList[cur.strIdx]+cur.leftIndex;
		*it_this || *it_other; ++it_this, ++it_other)
	{
		if(*it_this == *it_other)
			++LCP;
		else
			break;
	}

	return LCP;
}

bool SuffixArray::nodeHasStringIndex(const SANode &node, long long idx) const
{
	if (node.index <= idx && 
		(node.index + stringLenList[node.strIdx] - node.leftIndex - node.lcp) 
		> idx)
		return true;
	// else
	return false;
		
}

bool SuffixArray::nodeIsLTIndex(const SANode &node, long long idx) const
{
	return node.index < idx;
}

string SuffixArray::constructStringInNode(const SANode &node, int prefixIndex) const
{
	string res;
	for(auto it = stringList[node.strIdx] + node.leftIndex;
		it != stringList[node.strIdx] + prefixIndex; ++it)
		res += *it;

	return res;
}

bool SuffixArray::NodeCmp::operator()(const SANode &ths, const SANode &other) const
{
	for(auto it_this = stringList[ths.strIdx]+ths.leftIndex,
			it_other = stringList[other.strIdx]+other.leftIndex;
		*it_this  && *it_other;	++it_this, ++it_other)
	{
		if(*it_this > *it_other)
		{
			return false;
		}
		else if(*it_this < *it_other)
		{
			return true;
		}
	}

	return (stringLenList[ths.strIdx] - ths.leftIndex < 
			stringLenList[other.strIdx] - other.leftIndex) ? true : false;

}

void SuffixArray::printNode(const SANode &node) const
{
	string res;
	for(auto it = stringList[node.strIdx] + node.leftIndex; *it; ++it)
	{
		res += *it;
	}
	cout << "(" << res << ", index:" << node.index << ", lcp: " << node.lcp << ")" 
		 << endl;
}

void unitTests()
{
	char str1[] = "abracadabra";
	char str2[] = "abra";
	char str3[] = "cadavarzebra";
	SuffixArray sa(str1);
	sa.updateVector();
	sa.print();
	sa.add(str2);
	cout << endl;
	sa.updateVector();
	sa.print();
	cout << endl;
	sa.add(str3);
	sa.updateVector();
	sa.print();

	cout << sa.substringBinSearch(0) << endl;
	cout << sa.substringBinSearch(109) << endl;
	cout << sa.substringBinSearch(110) << endl;
	cout << sa.substringBinSearch(111) << endl;
	cout << sa.substringBinSearch(112) << endl;
	cout << sa.substringBinSearch(113) << endl;
	cout << sa.substringBinSearch(114) << endl;
	cout << sa.substringBinSearch(1) << endl;
	cout << sa.substringBinSearch(3) << endl;
	cout << sa.substringBinSearch(4) << endl;
	cout << sa.substringBinSearch(11) << endl;

	cout << endl << "SUBSTRINGS" << endl;
	sa.updateSubstringVec();
	sa.printSubstrings();
}

void solveFindStrings()
{
	int n;
	scanf("%d", &n);
	SuffixArray sa;
	char *s;
	for(int index = 0; index < n; ++index)
	{
		s = (char*)malloc(2000*sizeof(char));
		scanf("%s", s);
		sa.add(s);
	}
	sa.updateVector();
	int q;
	scanf("%d", &q);
	for(int query = 0; query < q; ++query)
	{
		long long idx;
		scanf("%llu", &idx);
		cout << sa.substringBinSearch(idx-1) << endl;
	}
}

int main(int argc, char *argv[])
{
//	solveFindStrings();
	unitTests();
	return 0;
}
