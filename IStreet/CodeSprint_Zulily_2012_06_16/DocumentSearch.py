

def main():
    nTests = int(raw_input())
    for test in xrange(nTests):
        docString = raw_input().strip()
        searchString = raw_input().strip()

        longestPrefix = []
        numSubstrings = 0
        curSubstring = searchString[:1]
        curSearchString = searchString

        while curSearchString and curSearchString[:1] in docString:
            #print curSearchString
            for index in xrange(len(curSearchString)):
                curSubstring = curSearchString[:index+1]
                #print curSubstring
                if curSubstring not in docString:
                    longestPrefix.append(curSearchString[:index])
                    docString = docString.replace(curSearchString[:index], "", 1)
                    #print longestPrefix
                    curSearchString = searchString[index:]
                    break
                elif len(curSearchString) == len(curSubstring):
                    longestPrefix.append(curSubstring)
                    curSearchString = None
                    break
                    


        print str(len("".join(longestPrefix))) + " " + str(len(longestPrefix))
                    
                

if __name__ == "__main__":
    main()
