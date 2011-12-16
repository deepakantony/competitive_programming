#!python

import fileinput

def isDoughnutHeavy( numOfDoughnuts, bagCapacity, weightOfEachDoughnut ):
    return numOfDoughnuts * weightOfEachDoughnut > bagCapacity

def main():
    numberOfTests = int(raw_input('Number of Tests: '))
    for n in xrange(numberOfTests):
        (n, k, w) = map(int, raw_input().strip().split())
        if isDoughnutHeavy(n, k, w):
            print "no" # harry cannot carry
        else:
            print "yes" # harry can carry
            

if __name__ == "__main__":
    main()
