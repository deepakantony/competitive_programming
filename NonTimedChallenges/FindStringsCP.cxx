#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;


// Convert string to char; but normalized (so subtract 'a' from it; start from 1)
void convertStringToIntChar(const string &str, int *output)
{
	int index = 0;
	for(auto it = str.begin(); it != str.end(); ++it) 
	{
		output[index++] = 1 + (int)(*it) - (int)'a';
#ifdef _DBUG
		cout << "(" << *it << "," << index-1 << ")";
#endif
	}
#ifdef _DBUG
	cout << endl;
#endif
	output[str.size()] = output[str.size()+1] = output[str.size()+2] = 0;
}

inline bool leq(int a1, int a2,   int b1, int b2) { // lexic. order for pairs
  return(a1 < b1 || a1 == b1 && a2 <= b2); 
}                                                   // and triples
inline bool leq(int a1, int a2, int a3,   int b1, int b2, int b3) {
  return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3)); 
}
// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
static void radixPass(int* a, int* b, int* r, int n, int K) 
{ // count occurrences
  int* c = new int[K + 1];                          // counter array
  for (int i = 0;  i <= K;  i++) c[i] = 0;         // reset counters
  for (int i = 0;  i < n;  i++) c[r[a[i]]]++;    // count occurences
  for (int i = 0, sum = 0;  i <= K;  i++) { // exclusive prefix sums
     int t = c[i];  c[i] = sum;  sum += t;
  }
  for (int i = 0;  i < n;  i++) b[c[r[a[i]]]++] = a[i];      // sort
  delete [] c;
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void constructSuffixArray(int* s, int* SA, int n, int K) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2; 
  int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0; 
  int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
  int* s0   = new int[n0];
  int* SA0  = new int[n0];
 
  // generate positions of mod 1 and mod  2 suffixes
  // the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
  for (int i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;

  // lsb radix sort the mod 1 and mod 2 triples
  radixPass(s12 , SA12, s+2, n02, K);
  radixPass(SA12, s12 , s+1, n02, K);  
  radixPass(s12 , SA12, s  , n02, K);

  // find lexicographic names of triples
  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (int i = 0;  i < n02;  i++) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) { 
      name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; } // left half
    else                  { s12[SA12[i]/3 + n0] = name; } // right half
  }

  // recurse if names are not yet unique
  if (name < n02) {
    constructSuffixArray(s12, SA12, n02, name);
    // store unique names in s12 using the suffix array 
    for (int i = 0;  i < n02;  i++) s12[SA12[i]] = i + 1;
  } else // generate the suffix array of s12 directly
    for (int i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i; 

  // stably sort the mod 0 suffixes from SA12 by their first character
  for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);

  // merge sorted SA0 suffixes and sorted SA12 suffixes
  for (int p=0,  t=n0-n1,  k=0;  k < n;  k++) {
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
    int i = GetI(); // pos of current offset 12 suffix
    int j = SA0[p]; // pos of current offset 0  suffix
    if (SA12[t] < n0 ? 
        leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
        leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
    { // suffix from SA12 is smaller
      SA[k] = i;  t++;
      if (t == n02) { // done --- only SA0 suffixes left
        for (k++;  p < n0;  p++, k++) SA[k] = SA0[p];
      }
    } else { 
      SA[k] = j;  p++; 
      if (p == n0)  { // done --- only SA12 suffixes left
        for (k++;  t < n02;  t++, k++) SA[k] = GetI(); 
      }
    }  
  } 
  delete [] s12; delete [] SA12; delete [] SA0; delete [] s0; 
}



template<class container_type>
void printContainer(container_type c)
{
	cout << "( ";
	for(auto it = c.begin(); it != c.end(); ++it)
		cout << *it << " ,";
	cout << " )" << endl;
}

template<class iterator_type>
void printContainer(iterator_type left, iterator_type right)
{
	cout << "( ";
	for(iterator_type it = left; it != right; ++it)
		cout << (int)*it << ", ";
	cout << " )" << endl;
	
}

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

	bool nodeLT(const SANode &node1, const SANode &node2) const;
	bool nodeEQ(const SANode &node1, const SANode &node2) const;
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
	vector<SANode> sortedSuffixSet; // constructed using linear suffix array algo

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
	if(sortedSuffixSet.empty())
		return;
	addAllSubstrings(*sortedSuffixSet.begin());
	auto it = sortedSuffixSet.begin();
	SANode prev = *it;
	SANode cur;
	++it;
	while(it != sortedSuffixSet.end())
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
#ifdef _DBUG
	cout << inpStr << endl;
#endif
	// convert to normalized char*
	int *inpStrChar = new int[inpStr.size()+3];;
	convertStringToIntChar(inpStr, inpStrChar);
#ifdef _DBUG
	printContainer(inpStrChar, inpStrChar+inpStr.size());
#endif

	int *suffixArray = new int[inpStr.size()];
	int K = 26; // 26 english chars supported

	constructSuffixArray(inpStrChar,  suffixArray, (int)inpStr.size(), K); 
#ifdef _DBUG
	printContainer(suffixArray, suffixArray+inpStr.size());
#endif
	vector<SANode> tempSortedSet(sortedSuffixSet.begin(), sortedSuffixSet.end());
	sortedSuffixSet.clear();
#ifdef _DBUG
	cout << "Sorting and merging begins" << endl;
#endif
	auto it_temp = tempSortedSet.begin();
	for(auto index = 0; index < inpStr.size(); ++index)
	{
		SANode newNode;
		newNode.strIdx = curIndex;
		newNode.leftIndex = suffixArray[index];
		
		while(it_temp != tempSortedSet.end() && nodeLT(*it_temp, newNode))
		{
			sortedSuffixSet.push_back(*it_temp);
			++it_temp;
		}
		if( (it_temp != tempSortedSet.end() && !nodeEQ(*it_temp, newNode)) 
			|| (it_temp == tempSortedSet.end()))
		{
			sortedSuffixSet.push_back(newNode);
		}
	}
	for(;it_temp != tempSortedSet.end(); ++it_temp)
		sortedSuffixSet.push_back(*it_temp);
#ifdef _DBUG
	cout << "Sofrting and merging complete" << endl;
#endif
/* // old sequential method
	int curIndex = stringList.size();
	stringList.push_back(inpStr);
	for(int leftIndex = 0; leftIndex < inpStr.size(); ++leftIndex)
	{
		SANode newNode(&stringList);
		newNode.strIdx = curIndex;
		newNode.leftIndex = leftIndex;
		suffixSet.insert(newNode);
	}
*/
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

bool SuffixArray::nodeLT(const SANode &node1, const SANode &node2) const
{
	return nc(node1, node2);
}

bool SuffixArray::nodeEQ(const SANode &node1, const SANode &node2) const
{
	auto node1Size = stringList[node1.strIdx].size() - node1.leftIndex;
	auto node2Size = stringList[node2.strIdx].size() - node2.leftIndex;

	if(node1Size != node2Size)
		return false;
	else
	{
		for(auto it_node1 = stringList[node1.strIdx].begin()+node1.leftIndex,
				it_node2 = stringList[node2.strIdx].begin()+node2.leftIndex;
			it_node1 != stringList[node1.strIdx].end() && 
				it_node2 != stringList[node2.strIdx].end(); 
			++it_node1, ++it_node2)
		{
			if(*it_node1 != *it_node2)
				return false;
		}
	}
	return true;
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
