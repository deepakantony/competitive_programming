/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
*/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <iterator>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()
#define EPS (1e-9)
#define FLT_EQ(x,y) ((fabs((x)-(y))) < EPS)

template<class CMP>
int array_count_simpler(const VI &A, int L, int R, CMP cmp) {
	int count = 0;
	int cur_subarray = 1;
	for(int i = L+1; i <= R; ++i) {
		if(cmp(A[i-1], A[i])) {
			cur_subarray += 1;
		}
		else
		{
			if(cur_subarray > 1) ++count;
			cur_subarray = 1;
		}
	}
	if(cur_subarray > 1) ++count;
	return count;
}

template<class CMP>
int array_count(const VI &A, int L, int R, CMP cmp) {
	int longest_subarray = 1;
	int longest_count = 1;
	int cur_subarray = 1;
	for(int i = L+1; i <= R; ++i) {
		if(cmp(A[i-1], A[i])) {
			cur_subarray += 1;
			if(cur_subarray == longest_subarray)
				longest_count++;
			else if (cur_subarray > longest_subarray)
			{
				longest_subarray = cur_subarray;
				longest_count = 1;
			}
		}
		else
		{
			cur_subarray = 1;
			if(cur_subarray == longest_subarray)
				longest_count++;
		}
	}
	return longest_count;
}

class SegmentTree {
	public:
	SegmentTree(const VI &A) :
	A(A)
	{
		root = create_st(0, A.size()-1);
	}

	~SegmentTree() {
		delete root;
	}

	bool lis_equal_lds(int L, int R) {
		NodeData data = get_nodedata(root, L, R);
		return data.lis_count == data.lds_count;
	}

	void print() {
		print_A();
		recurse_print(root, 0);
	}

	private:
	struct NodeData {
		int l, r;
		int lis_left;
		int lis_right;
		int left_is;
		int right_is;
		int lds_left;
		int lds_right;
		int left_ds;
		int right_ds;
		int lis_count;
		int lds_count;

		NodeData(int l, int r, int lis_l, int lis_r, int l_is, int r_is, int lds_l, int lds_r, int l_ds, int r_ds, int lis_count, int lds_count)
		:
		l(l),
		r(r),
		lis_left(lis_l),
		lis_right(lis_r),
		left_is(l_is),
		right_is(r_is),
		lds_left(lds_l),
		lds_right(lds_r),
		left_ds(l_ds),
		right_ds(r_ds),
		lis_count(lis_count),
		lds_count(lds_count)
		{}

		int lis_size() const { return lis_right - lis_left + 1; }
		int lds_size() const { return lds_right - lds_left + 1; }
		int left_is_size() const { return left_is - l + 1; }
		int right_is_size() const { return r - right_is + 1; }
		int left_ds_size() const { return left_ds - l + 1; }
		int right_ds_size() const { return r - right_ds + 1; }

		NodeData(){}
	};
	struct Node {
		NodeData data;
		Node *left;
		Node *right;

		Node(const NodeData &d, Node *l, Node *r)
		:
		data(d),
		left(l),
		right(r)
		{}

		~Node() {
			delete left;
			delete right;
		}
	};
	Node *root;
	VI A;

	Node *create_st(int l, int r) {
		assert(l <= r);
		if (l==r) return new Node(NodeData(l, r, l, r, l, r, l, r, l, r, 1, 1), nullptr, nullptr);
		else {
			int mid = l+(r-l)/2;
			Node *left = create_st(l, mid);
			Node *right = create_st(mid+1, r);
			NodeData data = create_data(l, r, left->data, right->data);
			return new Node(data, left, right);
		}
	}

	NodeData create_data(int l, int r, const NodeData &left_data, const NodeData &right_data) {
		NodeData new_data;
		new_data.l = l;
		new_data.r = r;

		// max lis
		{
			int l_max = left_data.lis_size();
			int r_max = right_data.lis_size();
			int mid_max = (A[left_data.r] < A[right_data.l]) ? left_data.right_is_size() + right_data.left_is_size() : 0;
			if(A[left_data.r] < A[right_data.l] && mid_max > l_max && mid_max > r_max) {
				new_data.lis_left = left_data.right_is;
				new_data.lis_right = right_data.left_is;
				new_data.lis_count = 1;
			}
			else if (l_max > r_max) {
				new_data.lis_left = left_data.lis_left;
				new_data.lis_right = left_data.lis_right;
				new_data.lis_count = left_data.lis_count;
				if(l_max == mid_max) new_data.lis_count += 1;
			}
			else {
				new_data.lis_left = right_data.lis_left;
				new_data.lis_right = right_data.lis_right;
				new_data.lis_count = right_data.lis_count;
				if(r_max == mid_max) new_data.lis_count += 1;
				if(r_max == l_max) new_data.lis_count += left_data.lis_count;
			}
		}

		// left is
		{
			new_data.left_is = (left_data.left_is < left_data.r || A[left_data.r] >= A[right_data.l]) ? left_data.left_is : right_data.left_is;
		}

		// right is
		{
			new_data.right_is = (right_data.right_is > right_data.l || A[left_data.r] >= A[right_data.l]) ? right_data.right_is : left_data.right_is;
		}

		// max lds
		{
			int l_max = left_data.lds_size();
			int r_max = right_data.lds_size();
			int mid_max = (A[left_data.r] > A[right_data.l]) ? left_data.right_ds_size() + right_data.left_ds_size() : 0;
			if(A[left_data.r] > A[right_data.l] && mid_max > l_max && mid_max > r_max) {
				new_data.lds_left = left_data.right_ds;
				new_data.lds_right = right_data.left_ds;
				new_data.lds_count = 1;
			}
			else if (l_max > r_max) {
				new_data.lds_left = left_data.lds_left;
				new_data.lds_right = left_data.lds_right;
				new_data.lds_count = left_data.lds_count;
				if(l_max == mid_max) new_data.lds_count += 1;
			}
			else {
				new_data.lds_left = right_data.lds_left;
				new_data.lds_right = right_data.lds_right;
				new_data.lds_count = right_data.lds_count;
				if(r_max == mid_max) new_data.lds_count += 1;
				if(r_max == l_max) new_data.lds_count += left_data.lds_count;
			}
		}

		// left ds
		{
			new_data.left_ds = (left_data.left_ds < left_data.r || A[left_data.r] <= A[right_data.l]) ? left_data.left_ds : right_data.left_ds;
		}

		// right ds
		{
			new_data.right_ds = (right_data.right_ds > right_data.l || A[left_data.r] <= A[right_data.l]) ? right_data.right_ds : left_data.right_ds;
		}

		return new_data;
	}

	NodeData get_nodedata(Node *root, int L, int R, int indent_spaces = 0) {
		assert(root != nullptr);
		assert(root->data.l <= L);
		assert(root->data.r >= R);

		//cout << " L = " << L << " R: " << R << endl;

		NodeData newdata;

		if(root->data.l == L && R == root->data.r) {
			newdata = root->data;
		}
		else {
			assert(root->data.l != root->data.r);
			if (R<=root->left->data.r) return get_nodedata(root->left, L, R);
			else if (L>= root->right->data.l) return get_nodedata(root->right, L, R);
			else {
				NodeData left_data = get_nodedata(root->left, L, root->left->data.r, indent_spaces + 4);
				NodeData right_data = get_nodedata(root->right, root->right->data.l, R, indent_spaces + 4);
				newdata = create_data(L, R, left_data, right_data);
			}
		}

		//cout << " **** " << endl;
		//print(newdata, indent_spaces);
		//cout << " **** " << endl;
		return newdata;
	}

	void print(const NodeData &data, int indent_spaces) {
		cout << string(indent_spaces, ' ') << "(" << data.l << ", " << data.r << ")" << endl;
		cout << string(indent_spaces, ' ') << "LIS: (" << data.lis_left << ", " << data.lis_right << ")" << endl;
		cout << string(indent_spaces, ' ') << "IS: (" << data.left_is << ", " << data.right_is << ")" << endl;
		cout << string(indent_spaces, ' ') << "LDS: (" << data.lds_left << ", " << data.lds_right << ")" << endl;
		cout << string(indent_spaces, ' ') << "DS: (" << data.left_ds << ", " << data.right_ds << ")" << endl;
		cout << string(indent_spaces, ' ') << "Count: (" << data.lis_count << ", " << data.lds_count << ")" << endl;
	}

	void recurse_print(const Node *root, int indent) {
		const static int indent_spaces = 4;
		print(root->data, indent*indent_spaces);
		if(root->left)
			recurse_print(root->left, indent+1);
		if(root->right)
			recurse_print(root->right, indent+1);
	}

	void print_A() {
		cout << "[";
		copy(A.begin(), A.end(), ostream_iterator<int>(cout, ","));
		cout << "]" <<endl;
	}
};

bool brute_force(const VI &A, int L, int R) {
	return array_count(A, L, R, less<int>()) == array_count(A, L, R, greater<int>());
}

bool brute_force_simpler(const VI &A, int L, int R) {
	return array_count_simpler(A, L, R, less<int>()) == array_count_simpler(A, L, R, greater<int>());
}

void solve() {
	int N, Q; cin >> N >> Q;
	VI A(N); REP(i, N) cin >> A[i];
	SegmentTree st(A);
	//st.print();
	while(Q--) {
		int L,R; cin >> L >> R;
		//if(st.lis_equal_lds(L-1,R-1))
		//if(brute_force(A, L-1, R-1))
		if(brute_force_simpler(A, L-1, R-1))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

bool test_A(const VI &A) {
	SegmentTree st(A);

	for(int L = 0; L < A.size()-1; ++L)
		for(int R = L+1; R < A.size(); ++R)
		{
			if(brute_force_simpler(A, L, R) != st.lis_equal_lds(L, R)) {
				cout << "*********************" << endl;
				cout << A.size() << " " << 1 << endl;
				copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
				cout << endl;
				cout << L << " " << R << endl;
				st.print();
				return false;
			}
		}
	return true;
}

void test()
{
	VI A1(100, 1);
	assert(test_A(A1));

	VI A2{1,2,1,2,1,2,1,2,1};
	assert(test_A(A2));

	srand(0);
	int t_count = 0;
	while(true) {
		cout << "\r" << t_count << flush;
		VI A;
		int A_size = rand()%5+2;
		REP(i, A_size) A.push_back(rand()%10);
		assert(test_A(A));
		t_count++;
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif
	// solve something here
	//solve();
	test();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
