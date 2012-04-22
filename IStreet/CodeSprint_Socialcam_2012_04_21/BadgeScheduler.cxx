#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <utility>
#include <string>
#include <fstream>

#define LL long long int
#define PLI pair< LL, int >


using namespace std;

class BadgeScheduler {
public:
	BadgeScheduler(char *filename) 
		: schedule(), idScheduleMap() {
		// read from file
		ifstream ifs(filename);
		LL timestamp; int userid;
		while(ifs.good()) {
			ifs >> userid >> timestamp;
			if(ifs.good())
				this->setId(userid, timestamp);
		}
		ifs.close();
	}
	
	void setId(int userid, LL timestamp) {
		PLI entryToInsert = make_pair(timestamp, userid);
		del(userid); // delete if exists
		idScheduleMap[userid] = timestamp;
		schedule.insert(entryToInsert);
	}

	void list(LL timestamp) {
		int first = 1;
		for(auto val: schedule) {
			if(val.first > timestamp) break;
			if(first == 1) {
				printf("%d", val.second);
				first = 0;
			}
			else printf(" %d", val.second);
		}
		printf("\n");
	}

	void del(int userid) {
		map<int, LL>::iterator it = idScheduleMap.find(userid);
		PLI itemToFind = make_pair(it->second, it->first);
		if(it != idScheduleMap.end()) { 
			schedule.erase(itemToFind);
			idScheduleMap.erase(it);
		}
	}
	void clear() {
		schedule.clear();
		idScheduleMap.clear();
	}

	void writeToFile(char *filename) {
		ofstream ofs(filename);
		if(ofs.good()) {
			for(auto val: idScheduleMap) {
				ofs << val.first << " " << val.second << endl;
			}
		}
		ofs.close();
	}

private:
	set< PLI > schedule;
	map<int , LL> idScheduleMap;
};

int main(int argc, char *argv[])
{
	char filename[] = "deebee_persist.txt";
	BadgeScheduler bScheduler(filename);
	int nOps; scanf("%d", &nOps);
	char operation[10];
	int userid;
	LL timestamp;
	while(nOps--) {
		scanf(" %s", operation);
		if(strcmp(operation, "set") == 0) {
			scanf(" %d %lld", &userid, &timestamp);
			bScheduler.setId(userid, timestamp);
		}
		else if(strcmp(operation, "del") == 0) {
			scanf(" %d", &userid);
			bScheduler.del(userid);
		}
		else if(strcmp(operation, "list") == 0) {
			scanf(" %lld", &timestamp);
			bScheduler.list(timestamp);
		}
		else if(strcmp(operation, "clear") == 0) {
			bScheduler.clear();
		}
	}

	bScheduler.writeToFile(filename);

	return 0;
}
