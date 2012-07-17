#include <cstdio>

using namespace std;

template<typename T>
class Node {
public:
	Node *next;
	T data;
	int size;
};

template<typename T>
class BST {
public:
	BST() {}

private:
	Node<T> root;
};


int main(int argc, char *argv[])
{
	return 0;
}
