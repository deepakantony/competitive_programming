#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
// I know i'm not supposed to use map but I don't have time for implementing
// a B+Tree.
#include <map>

using namespace std;

class Database 
{
public:
	static Database* getInstance() {
		if(!instance) {
			instance = new Database();
		}
		return instance;
	}

	void performOperation(const string &op) {
		istringstream ss(op);
		vector<string> operation;
		istream_iterator<string> it(ss);
		istream_iterator<string> end;
		copy(it, end, back_inserter(operation));

		if( (operation[0] == "SET" || 
			 operation[0] == "set") && 
			operation.size() == 3)
		{
			set(operation[1], operation[2]);
		}
		else if( (operation[0] == "GET" || 
				  operation[0] == "get") &&
				 operation.size() == 2)
		{
			cout << get(operation[1]) << endl;
		}
		else if( operation[0] == "COMMIT" || 
			operation[0] == "commit" )
		{
			commit();
		}
		else if( operation[0] == "ROLLBACK" ||
			operation[0] == "rollback" )
		{
			clearTemp();
		}
	}

	string get(const string &key) const {
		if(temporaryStore.find(key) != temporaryStore.end())
			return temporaryStore.find(key)->second;
		if(permanentStore.find(key) != permanentStore.end())
			return permanentStore.find(key)->second;
		return string("");
	}

	void set(const string &key, const string &value) {
		temporaryStore[key] = value;
	}

	void commit() {
		for(map<string,string>::iterator it = temporaryStore.begin();
			it != temporaryStore.end(); ++it)
		{
			permanentStore[it->first] = it->second;
		}
	}

	void clearTemp() {
		temporaryStore.clear();
	}

private:
	Database() : permanentStore(), temporaryStore(){
	}
	map<string,string> permanentStore;
	map<string,string> temporaryStore;

private:
	static Database *instance;
};

Database* Database::instance = 0;

void keyValue(vector<string> &a,int n) {
	Database::getInstance()->clearTemp();
	for(vector<string>::iterator it = a.begin();
		it != a.end(); ++it)
	{
		Database::getInstance()->performOperation(*it);
	}

}

int main(int argc, char *argv[])
{
	while(true)
	{
		cout << "$$>";
		char q[100];
		cin.getline(q, 100);

		Database::getInstance()->performOperation(string(q));
	}
	return 0;
}
