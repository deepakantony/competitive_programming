#!/usr/bin/env python

# Problem originally found @ 
# http://www.interviewstreet.com/recruit/challenges/solve/view/4e1491425cf10/4efa210eb70ac
#
# Find Strings (25 points)
# You are given 'n' strings w1, w2, ......, wn. Let Si denote the set of strings
# formed by considering all unique substrings of the string wi. A substring is 
# defined as a contiguous sequence of one or more characters in the string. 
# More information on substrings can be found here. Let 'S' = {S1 U S2 U .... Sn}
# .i.e 'S' is a set of strings formed by considering all the unique strings in 
# all sets S1, S2, ..... Sn. You will be given many queries and for each query, 
# you will be given an integer 'k'. Your task is to output the lexicographically 
# kth smallest string from the set 'S'.
#  
# Input:
# The first line of input contains a single integer 'n', denoting the number of 
# strings. Each of the next 'n' lines consists of a string. The string on the 
# ith line (1<=i<=n) is denoted by wi and has a length mi. The next line consists 
# of a single integer 'q', denoting the number of queries. Each of the next 'q' 
# lines consists of a single integer 'k'.
# Note: The input strings consist only of lowercase english alphabets 'a' - 'z'.
#  
# Output:
# Output 'q' lines, where the ith line consists of a string which is the answer 
# to the ith query. If the input is invalid ('k' > |S|), output "INVALID" 
# (quotes for clarity) for that case.
# 
# Constraints:
# 1<=n<=50
# 1<=mi<=2000
# 1<=q<=500
# 1<=k<=1000000000
# 
# Sample Input:
# 2
# aab
# aac
# 3
# 3
# 8
# 23
# 
# Sample Output:
# aab
# c
# INVALID
# 
# Explanation:
# For the sample test case, we have 2 strings "aab" and "aac".
# S1 = {"a", "aa", "aab", "ab", "b"} . These are the 5 unique substrings of "aab".
# S2 = {"a", "aa", "aac",  "ac", "c" } . These are the 5 unique substrings of "aac".
# Now, S = {S1 U S2} = {"a", "aa", "aab", "aac", "ab", "ac", "b", "c"}. Totally, 
# 8 unique strings are present in the set 'S'. 
# The lexicographically 3rd smallest string in 'S' is "aab" and the 
# lexicographically 8th smallest string in 'S' is "c". Since there are only 8 
# distinct substrings, the answer to the last query is "INVALID".
# 

import sys
import time

# This is tricky problem; you need to store all the substring and sort them
# lexicographically. This would take lot of space. But, we can use index array
# for all the substrings. This way we can save space by not storing whole 
# strings

# I tried using the regular list and tuple; using quicksort to sort and another
# O(n) to remove duplicates. It takes too long. I'll try a self-balancing
# binary tree now. Hopefully it should be fast.

class Node:
    def __init__(self, val):
        self.left = None
        self.right = None
        self.key = val

class AVLSubString:
    def __init__(self):
        self.subStrings = None
        self.inpString = None
        self.length = 0

    def __getitem__(self, key):
        (start, end) = self.findFromIndex(key)
        return self.inpString[start:end]

    def append(self, inStr):
        curLen = len(self.inpString)
        self.inpString += inStr
        newLen = len(self.inpString)
        for i in xrange(curLen, newLen):
            for j in xrange(i, newLen):
                self.insert( (i, j+1) ) # insert a tuple of start and end indices
                self.length += 1

    def eq(self, key1, key2):
        len1 = key1[1] - key1[0]
        len2 = key2[1] - key2[0]
        if len1 != len2:
            return False

        index1 = key1[0]
        index2 = key2[0]
        while index1 < key1[1]:
            if self.inpString[index1] != self.inpString[index2]:
                return False
            index1 += 1
            index2 += 1
            
        return True

    def lt(self, key1, key2)
        len1 = key1[1] - key1[0]
        len2 = key2[1] - key2[0]

        if len1 != len2:
            return False

        index1 = key1[0]
        index2 = key2[0]
        while index1 < key1[1]:
            if self.inpString[index1] != self.inpString[index2]:
                return False
            
        return True


class SubStringListIndex:
    def __init__(self):
        self.subStringList = []
        self.stringList = []
        self.length = 0
    
    # sort the substring list  
    def sort(self):
        self.quicksort(0, len(self.subStringList)-1)

    # quicksort
    def quicksort(self, left, right):
        if left < right:
            pivot = left + (right-left)/2
            store = self.partition(left, right, pivot)
            self.quicksort(left, store-1)
            self.quicksort(store+1, right)

    def listSwap(self, index1, index2):
        temp = self.subStringList[index1]
        self.subStringList[index1] = self.subStringList[index2]
        self.subStringList[index2] = temp

    def partition(self, left, right, pivot):
        self.listSwap(right, pivot)
        store = left
        for index in xrange(left, right):
            if self[index] > self[right]:
                self.listSwap(index, store)
                store += 1
        self.listSwap(store, right)
        return store

        
    # add a string to the list and append all it's substrings to the substring 
    # list
    def append(self, inStr):
        self.stringList.append(inStr)
        inStrLen = len(inStr)
        stringListLen = len(self.stringList)
        for i in xrange(inStrLen):
            for j in range(i, inStrLen):
                self.subStringList.append( (stringListLen-1, i, j+1) )
                self.length += 1

    def removeDups(self):
        self.subStringList2 = []
        ssListLen = len(self.subStringList)
        curItem = ""
        topItem = ""
        tempLength = 0
        for index in xrange(ssListLen-1, -1, -1):
            curItem = self[index]
            tempStore = self.subStringList.pop()
            if curItem != topItem:
                self.subStringList2.append(tempStore)
                topItem = curItem
                tempLength += 1
                
        self.length = tempLength

    # index operator
    def __getitem__(self, key):
        if self.length <= 0:
            return None
        if len(self.subStringList) > 0:
            (stringIndex, start, end) = self.subStringList[key]
            return self.stringList[stringIndex][start:end]
        else:
            (stringIndex, start, end) = self.subStringList2[key]
            return self.stringList[stringIndex][start:end]

    # string representation
    def __str__(self):
        return str([ self[x] for x in xrange(self.length)])


def main(argv):
    start = time.time()
    inp = sys.stdin
    out = sys.stdout
    if len(argv) > 1:
        try:
            inp = open(argv[1], 'r')
            if len(argv) > 2:
                out = open(argv[2], 'w')
        except IOError as err:
            print err

    # First get the number of strings
    nStrings = int(inp.readline())
    # Then the strings
    subStringList = SubStringListIndex()
    for x in xrange(nStrings):
        curStr = inp.readline().rstrip()
        subStringList.append(curStr)

    # sort the list
    subStringList.sort()

    # remove duplicates and sort it ascending
    subStringList.removeDups()

    # queries
    nQueries = int(inp.readline())
    for x in xrange(nQueries):
        query = int(inp.readline())
        if query > subStringList.length:
            print "INVALID"
        else:
            print subStringList[query-1]

    if len(argv) > 1 :
        print "Total Executaion time %f secs" % (time.time()-start)
        inp.close()
        if len(argv) > 2 :
            out.close()

if __name__ == "__main__":
    main(sys.argv)
