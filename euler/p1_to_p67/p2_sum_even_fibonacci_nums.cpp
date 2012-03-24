#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

#define N 4000000

int main() {
    // starting even number is 2
    long sum_fibo = 2;
    
    // previous terms
    long prev = 2;

    // current number
    long cur = 3; 
    
    while(cur < 4000000) {
        if(cur % 2 == 0)
            sum_fibo += cur;

        int temp = cur;
        cur += prev;
        prev = temp;
    }

    cout << sum_fibo << endl;

    return 0;
}

