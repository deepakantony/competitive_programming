import sys

def main():
    inp = sys.stdin
    if len(sys.argv) > 1:
        inp = open(sys.argv[1], 'r')
    inpTemp = {}
    aToz = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    for x in aToz:
        names = inp.readline().split()
        inpTemp[x] = names[1:]
    nIntervals = int(inp.readline().rstrip())
    for x in xrange(nIntervals):
        alerts = inp.readline().split()
        #print alerts
        callNamesSet = set()
        for alert in alerts:
            if alert[1] == '1':
                for z in inpTemp[alert[0]]:
                    callNamesSet.add(z)
        callNamesList = [ y for y in callNamesSet ]
        callNamesList.sort()
        for name in callNamesList:
            print name + " ",
        print

if __name__ == "__main__":
    main()
