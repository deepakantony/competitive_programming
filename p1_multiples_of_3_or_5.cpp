#include <iostream>

using std::cout;
using std::endl;

#define N 1000

int main(int argc, char* argv[]) {
    int sum = 0;
	for(int i = 1; i < N; i++)
        if(i % 3 == 0)
            sum += i;
        else if(i % 5 == 0)
            sum += i;
            
    cout << sum << endl;

    return 0;
}    
