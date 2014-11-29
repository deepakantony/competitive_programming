#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Circular Buffer class - provide method sfor append n elements, remove n
// elements and list all elements.
template<typename ItemType>
class CircularBuffer 
{
public:
	// initialize the buffer of the given size. The +1 used here helps in 
	// cleaner implementatoin. It means one slot will always be unused.
	CircularBuffer(int size) : _buf(size+1), _front(0), _back(0){}

	// Append an element to the buffer. If buffer is full replace old entries.
	void append(const ItemType &elem) {
		_buf[_back] = elem;
		next(_back);
		if(_back == _front) next(_front);
	}

	// Remove first N elements from the buffer.
	void remove(int N = 1) {
		if(N >= bufSize()) 
			_front = _back = 0;
		else if(_front < _back || _front+N < _buf.size())
			_front = _front+N;
		else
			_front = N - _buf.size() + _front;
	}

	// List all the elements.
	void list() {
		for(int index = _front; index != _back; next(index)) 
			cout << _buf[index] << endl;
	}
private:
	// advances the given index by 1
	void next(int &index) {
		index = (index+1)%_buf.size();
	}

	// checks if the buffer is empty
	bool empty() {
		return _front == _back;
	}

	// returns the number of elements in the buffer
	int bufSize() {
		if(_front <= _back) 
			return _back-_front;
		// else
		return _buf.size()-_front + _back;
	}

	vector<ItemType> _buf;
	int _front, _back;
};

int main(int argc, char *argv[]) 
{
	string inputElement; 
	int N; // size of the buffer
	cin >> N;
	CircularBuffer<string> buffer(N);
	char operation;
	bool quit = false;
	while(!quit) {
		cin >> operation;
		switch(operation) {
		case 'A': // append N elements
			cin >> N;
			while(N--) {
				cin >> inputElement;
				buffer.append(inputElement);
			}
			break;
		case 'R': // remove
			cin >> N;
			buffer.remove(N);
			break;
		case 'L': 
			buffer.list();
			break;
		case 'Q':
			quit = true;
			break;
		}
	}
	return 0;
}
