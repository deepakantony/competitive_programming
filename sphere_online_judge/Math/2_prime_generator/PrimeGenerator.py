import math

class PrimeList:
    def __init__(self, n):
        self.list = [True]*(n+1)
        self.size = n+1

        self.list[0] = self.list[1] = False

        for index in xrange(2, math.ceil(math.sqrt(self.size)), 2):
            if self.list[index]:
                prime = self.list[index]
                for nonPrimes in xrange(prime*prime, self.size):
                    self.list[nonPrimes] = False

    def setitem(self, k, v):
        self.list[k] = v

    def getitem(self, k):
        return self.list[k]

def isPrime(num):
    if num == 2 or num == 3 or num == 5 or num == 7:
        return True
    if num%2 == 0 or num%3 == 0 or num <= 10:
        return False

    sqrt_1by6 = int(math.ceil((math.sqrt(num) - 1)/6))
    # primes occur every 6n-1 and 6n+1 after 2 and 3
    for n in xrange(1, sqrt_1by6+1):
        if num % (6*n-1) == 0:
            return False
        if num % (6*n+1) == 0:
            return False
    # num is not divisible by any number up-till it's sqrt
    return True

def generatePrimes(size=10000000000):
    pass

def printPrime(lowRange, highRange ):
    for num in xrange(lowRange, highRange+1):
        if isPrime(num):
            print num

def main():
    #primeList = PrimeList(100000000)
    numOfTests = int(raw_input().strip())
    for dummyIndex in xrange(numOfTests):
        (lowRange, highRange) = tuple(map(int, raw_input().strip().split()))
        printPrime(lowRange, highRange)
        print

if __name__ == "__main__":
    main()
