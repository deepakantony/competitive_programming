# Alice is a kindergarden teacher. She wants to give some candies to the children
#  in her class.  All the children sit in a line and each  of them  has a rating 
# score according to his or her usual performance.  Alice wants to give at least 
# 1 candy for each child.Children get jealous of their immediate neighbors, so 
# if two children sit next to each other then the one with the higher rating must 
# get more candies. Alice wants to save money, so she wants to minimize the total 
# number of candies.
#  
#  
# Input
#  
# The first line of the input is an integer N, the number of children in Alice's 
# class. Each of the following N lines contains an integer indicates the rating 
# of each child.
#  
# Ouput
#  
# Output a single line containing the minimum number of candies Alice must give.
#  
# Sample Input
#  
# 3
# 1
# 2
# 2
#  
# Sample Ouput
#  
# 4
#  
# Explanation
#  
# The number of candies Alice must give are 1, 2 and 1.
#  
# Constraints:
#  
# N and the rating  of each child are no larger than 10^5.
# 

# The candies problem can be solved very easily. The idea is to scan the list
# of ratings in forward direction and then the backward direction. In both scan
# any increasing sequence increases the candies from the previous child. Once
# both sequences are calculated, just find the max of these two scans for every
# child and sum them; that'll be the final answer.

import sys

def main():
    N = int(raw_input().strip())
    ratingList = []
    for x in xrange(N):
        ratingList.append(int(raw_input().strip()))

    forwardCandies = [1]*N
    prevCandy = 1
    for index, rating in enumerate(ratingList[1:]):
        if rating > ratingList[index]:
            forwardCandies[index+1] = prevCandy = prevCandy + 1
        else:
            prevCandy = 1

    backwardCandies = [1]*N
    prevCandy = 1

    for index, rating in enumerate(ratingList[N-2::-1]): # reverse list
        if rating > ratingList[N-1-index]:
            backwardCandies[N-2-index] = prevCandy = prevCandy + 1
        else:
            prevCandy = 1

    res = 0

    for index in xrange(N):
        #print ratingList[index], forwardCandies[index], backwardCandies[index], max(forwardCandies[index], backwardCandies[index]) 
        res += max(forwardCandies[index], backwardCandies[index])
    print res

if __name__ == "__main__":
    main()
