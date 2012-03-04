#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class SuffixArray
{
public:
	SuffixArray(); // default initialization for adding strings later
	SuffixArray(const string &inpStr); // init with a string

	void add(const string &inpStr);
	void updateVector();
	void updateSubstringVec();
	string substring(long long idx);
	string substringBinSearch(long long idx);
	void print() const;
	void printSubstrings() const;
private:
	void updateSuffixArray(const string &inpStr);

	struct SANode 
	{
		SANode() 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0){}
		SANode(vector<string> *sl) 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0) {}
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
		NodeCmp(vector<string> &sl) : stringList(sl) {}
		bool operator() (const SANode &ths, const SANode &other) const; // this will be used by set for sorting	
		vector<string> &stringList;
	} nc;
	void printNode(const SANode &node) const;

	set<SANode,NodeCmp> suffixSet; // this eliminates duplicates
	vector<SANode> suffixVec; // random access
	long long substringsMaxIndex; // number of distinct substrings - 1
	vector<string> stringList; // list of strings and suffixs

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
	: nc(stringList), suffixSet(nc)
{
}

SuffixArray::SuffixArray(const string &inpStr)
	: nc(stringList), suffixSet(nc)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::add(const string &inpStr)
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
		cur.index = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex);
		suffixVec.push_back(cur);

		prev = cur;
		++it;
	}
	substringsMaxIndex = 0ll + prev.index + stringList[prev.strIdx].size() - 
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
		cur.index = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex);
		addAllSubstrings(cur);

		prev = cur;
		++it;
	}
}

void SuffixArray::addAllSubstrings(const SANode &node)
{
	for(int rightIndex = node.leftIndex + node.lcp + 1;
		rightIndex <= stringList[node.strIdx].size(); ++rightIndex)
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
	for(auto it = stringList[subNode.strIdx].begin() + subNode.left;
		it != stringList[subNode.strIdx].begin() + subNode.right; ++it)
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

void SuffixArray::updateSuffixArray(const string &inpStr)
{
	int curIndex = stringList.size();
	stringList.push_back(inpStr);
	for(int leftIndex = 0; leftIndex < inpStr.size(); ++leftIndex)
	{
		SANode newNode(&stringList);
		newNode.strIdx = curIndex;
		newNode.leftIndex = leftIndex;
		suffixSet.insert(newNode);
	}
}

int SuffixArray::findLCP(const SANode &prev, const SANode &cur) const
{
	int LCP = 0;
	for(auto it_this = stringList[prev.strIdx].begin()+prev.leftIndex,
			it_other = stringList[cur.strIdx].begin()+cur.leftIndex;
		it_this != stringList[prev.strIdx].end() || 
			it_other != stringList[cur.strIdx].end(); 
		++it_this, ++it_other)
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
		(node.index + stringList[node.strIdx].size() 
		 - node.leftIndex - node.lcp) > idx)
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
	for(auto it = stringList[node.strIdx].begin() + node.leftIndex;
		it != stringList[node.strIdx].begin() + prefixIndex; ++it)
		res += *it;

	return res;
}

bool SuffixArray::NodeCmp::operator()(const SANode &ths, const SANode &other) const
{
	for(auto it_this = stringList[ths.strIdx].begin()+ths.leftIndex,
			it_other = stringList[other.strIdx].begin()+other.leftIndex;
		it_this != stringList[ths.strIdx].end() && 
			it_other != stringList[other.strIdx].end(); 
		++it_this, ++it_other)
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

	return (stringList[ths.strIdx].size() - ths.leftIndex < 
			stringList[other.strIdx].size() - other.leftIndex) ? true : false;

}

void SuffixArray::printNode(const SANode &node) const
{
	string res;
	for(auto it = stringList[node.strIdx].begin() + node.leftIndex;
		it != stringList[node.strIdx].end(); ++it)
	{
		res += *it;
	}
	cout << "(" << res << ", index:" << node.index << ", lcp: " << node.lcp << ")" 
		 << endl;
}

void unitTests()
{
	SuffixArray sa("abracadabra");
	sa.updateVector();
	sa.print();
	sa.add("abra");
	cout << endl;
	sa.updateVector();
	sa.print();
	cout << endl;
	sa.add("cadavarzebra");
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
	cin >> n;
	SuffixArray sa;
	for(int index = 0; index < n; ++index)
	{
		string s;
		cin >> s;
		sa.add(s);
	}
	sa.updateSubstringVec();
	int q;
	cin >> q;
	for(int query = 0; query < q; ++query)
	{
		long long idx;
		cin >> idx;
		cout << sa.substring(idx-1) << endl;
	}
}

int main(int argc, char *argv[])
{
	solveFindStrings();
//	unitTests();
	return 0;
}
