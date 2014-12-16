#include <iostream>
#include <cmath>
#include <inttypes.h>

using std::cout;
using std::endl;

const long long int N = 600851475143;

bool is_prime(long long int n) {
    long long int sqrt_n = (long)sqrt(n);

    if(n < 2) return false;

    for(long long int i = 2; i < sqrt_n; i++)
        if(n % i == 0)
            return false;
            
    return true;
}

int main(int argc, char* argv[]) {
    long long int largest_factor = 1;

    for(long long int i = 2; i * i <= N; i++)
        if(N % i == 0 && is_prime(i))
            largest_factor = i;

    cout << largest_factor << endl;

    return 0;
}
