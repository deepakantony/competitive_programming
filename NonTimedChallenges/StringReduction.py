# String Reduction - problem description
# 
# Given a string consisting of a,b and c's, we can perform the following 
# operation: Take any two adjacent distinct characters and replace it with 
# the third character. For example, if 'a' and 'c' are adjacent, they can 
# replaced with 'b'. What is the smallest string which can result by 
# applying this operation repeatedly?
# 
# Input:
# The first line contains the number of test cases T. T test cases follow. 
# Each case contains the string you start with.
# 
# Output:
# Output T lines, one for each test case containing the smallest length of 
# the resultant string after applying the operations optimally.
# 
# Constraints:
# 1 <= T <= 100
# The string will have at most 100 characters.
# 
# Sample Input:
# 3
# cab
# bcab
# ccccc
# 
# Sample Output:
# 2
# 1
# 5
# 
# Explanation:
# For the first case, you can either get cab -> cc or cab -> bb, resulting 
# in a string of length 2.
# For the second case, one optimal solution is: bcab -> aab -> ac -> b. No 
# more operations can be applied and the resultant string has length 1.
# For the third case, no operations can be performed and so the answer is 5.

# This is fairly straight forward to solve once you play with it a bit.
# Few things I've used in my algorithm
# * try to reduce large repeating loops first. For example in abcbbbbbb try
# to reduce cbbbbbb first.
# * handle corner cases separately

import sys

xorableChars = {'a':1, 'b':2, 'c':3}
reducedChars = { 1: 'a', 2: 'b', 3:'c' }

# This will perform the first possible reduction
# Here are few possibilities
# if the input is 'aaaaaba' 'ca' will be returned
# if the input is 'abcccc' 'ab' will be returned
# if the input is 'abcacb' 'ccacb' will be returned
def reduceFirst(inputStr):
    # base cases
    if len(inputStr) == 1:
        return inputStr
    if len(inputStr) == 2:
        xorChars = xorableChars[inputStr[0]] ^ xorableChars[inputStr[1]]
        if xorChars == 0:
            return inputStr
        else:
            return reducedChars[xorChars]

    firstRepeatIndex = 0
    firstNonRepeatAfter = 0
    res = ''
    prevChar = ''
    for x in xrange(0, len(inputStr)):
        if prevChar == inputStr[x]:
            firstRepeatIndex = x-1
            firstNonRepeatAfter = firstRepeatIndex
            for y in xrange(x+1, len(inputStr)):
                if prevChar != inputStr[y]:
                    firstNonRepeatAfter = y
                    break
            break
        else:
            prevChar = inputStr[x]
    
    if firstNonRepeatAfter == 0:
        if inputStr[0] == inputStr[1]: 
            # this will cover cases such as 'aaaaaa'
            return inputStr
        else:
            # this will cover cases such as 'abcac' i.e. no repeats 
            return (reducedChars[xorableChars[inputStr[0]] ^ 
                                xorableChars[inputStr[1]]] + inputStr[2:])
    
    if firstNonRepeatAfter == firstRepeatIndex:
        # This is if there is no character after the repeating character
        firstNonRepeatAfter = firstNonRepeatAfter-1
        res = inputStr[0:firstNonRepeatAfter]
        if (firstRepeatIndex - len(inputStr)) % 2 == 0:
            # i.e. abb - even repeating chars
            res += inputStr[firstNonRepeatAfter]
        else:
            # i.e. abbb - odd repeating chars
            res += reducedChars[xorableChars[inputStr[firstNonRepeatAfter]] ^
                                xorableChars[inputStr[firstRepeatIndex]]]
        return res
    else:
        res = inputStr[0:firstNonRepeatAfter-1]
#        if (firstNonRepeatAfter - firstRepeatIndex) %2 == 0:
            # see the description above
#            res += inputStr[firstNonRepeatAfter]
#        else:
        res += reducedChars[xorableChars[inputStr[firstNonRepeatAfter]] ^
                                xorableChars[inputStr[firstRepeatIndex]]]
        return res + inputStr[firstNonRepeatAfter+1:len(inputStr)]
        

def stringReduce(startingStr):
    res = startingStr
    while True:
        resTemp = reduceFirst(res)
#        print resTemp
        if resTemp == res:
            return res
        res = resTemp

def main():
    inp = sys.stdin
    nTests = int(inp.readline())

    for test in xrange(nTests):
        startingString = inp.readline().rstrip()
        outputStr = stringReduce(startingString)
        #print (outputStr, len(outputStr))
        print len(outputStr)

if __name__ == '__main__':
    main()
