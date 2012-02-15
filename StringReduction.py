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
    while x in xrange(0, len(inputStr)):
        if prevChar == inputStr[x]:
            firstRepeatIndex = x-1
            firstNonRepeatAfter = firstRepeatIndex
            for y in xrange(x+1, len(inputStr)):
                if prevChar != inputStr[y]:
                    firstNonRepeatAfter = y
            break
        else:
            prevChar = inputStr[x]
    
    if firstNonRepeatAfter == 0:
        

def stringReduce(startingStr):
    res = startingStr
    while True:
        resTemp = reduceFirst(res)
        if resTemp == res:
            return res
        res = resTemp

def main():
    inp = sys.stdin
    out = sys.stdout
    nTests = int(inp.readline())

    for test in xrange(nTests):
        startingString = inp.readline()
        out.write(str(len(stringReduce(startingString)))+'\n')

if __name__ == '__main__':
    main()
