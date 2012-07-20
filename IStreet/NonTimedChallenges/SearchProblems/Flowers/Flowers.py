# this has to be the easiest problem in interviewstreet;
# This is easily solved when you realize that, all you need to do is to sort
# the cost list in descending order and assign to each person in sequence.

import sys

def main():
    (N, K) = tuple( [ int(x) for x in  raw_input().strip().split()] )
    costList = [ int(x) for x in raw_input().strip().split() ]
    costList.sort(reverse=True)

    xflowers = 0
    money = 0
    for cost in costList:
        money += ((xflowers/K)+1)*cost
        xflowers += 1
    print money

if __name__ == "__main__":
    main()
