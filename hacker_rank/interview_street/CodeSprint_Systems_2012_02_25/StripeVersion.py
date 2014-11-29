import sys
import json
import hashlib

class CommitData:
    def __init__(self, commitString):
        self.commitString = commitString
        tempList = commitString.split('\n')
        self.payload = tempList.pop()
        self.sha1 = hashlib.sha1(commitString).hexdigest()
        self.children = set()
        if len(tempList) == 1:
            payloadSha1 = hashlib.sha1(self.payload).hexdigest()
            child = tempList.pop().split().pop()
            if child != payloadSha1:
                self.children.add(child)
        for child in tempList:
            self.children.add(child.split().pop())

        self.parents = set()
        self.ordered = False

    def __str__(self):
        return self.commitString
    def __repr__(self):
        return self.commitString

class ChangeLogData:
    def __init__(self, jsonString):
        self.orderedChangeLog = []
        self.changeLogJson = json.loads(jsonString)
        self.changeLog = []
        self.createChangeLogFromJson()
        self.changeLogTable = {}
        self.createChangelogTable()
        self.notifyChildren()
        self.orderedChangeLog = []
        self.createOrderedLog()

    def createChangeLogFromJson(self):
        for commitString in self.changeLogJson:
            commit = CommitData(commitString)
            self.changeLog.append(commit)

    def createChangelogTable(self):
        for commit in self.changeLog:
            self.changeLogTable[commit.sha1] = commit

    def notifyChildren(self):
        for sha1, commit in self.changeLogTable.iteritems():
            for child in commit.children:
                self.changeLogTable[child].parents.add(commit)

    def recurseOrder(self, commit):
        for parent in commit.parents:
            if not parent.ordered:
                self.recurseOrder(parent)
        self.orderedChangeLog.append(commit)
        commit.ordered = True

    def createOrderedLog(self):
        for sha1, commit in self.changeLogTable.iteritems():
            if not commit.ordered:
                self.recurseOrder(commit)

    def printJsonOrdered(self):
        tempList = []
        for commit in self.orderedChangeLog:
            tempList.append(str(commit))
        print json.dumps(tempList, separators=(',',':'))

    def printOrdered(self):
        print self.orderedChangeLog

def main():
    jsonString = sys.stdin.readline()
    log = ChangeLogData(jsonString)
    log.printJsonOrdered()
#    log.printOrdered()

if __name__ == "__main__":
    main()
