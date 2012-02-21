#include <iostream>
#include <string>

using namespace std;

class ImplicitNode
{
public:
	ImplicitNode(int l, int r) 
		:left(l), right(r) {
	}
	bool isEmpty() {
		return left > right;
	}

private:
	int left, right;
}

class State
{
public:
	State() 
		:leaf(true) {
	}
	void addTransition(ImplicitNode) {
		transitions.insert
	bool isLeaf();
private:
	unordered_map<char, pair<ImplicitNode, State* > > transitions;
	bool leaf;
}

class STree 
{
	
