def main():
    T = int(raw_input())
    for test in xrange(T):
        N = int(raw_input())
        buildingList = raw_input().strip()
        totalStanding = N
        for index, building in enumerate(buildingList):
            if building == '1' or \
                    (index > 0 and buildingList[index-1] == '1') or \
                    (index < N-1 and buildingList[index+1] == '1'):
                totalStanding -= 1
        print totalStanding


if __name__ == "__main__":
    main()
