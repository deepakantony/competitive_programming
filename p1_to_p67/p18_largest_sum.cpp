#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int largest_sum(vector< vector<int> > triangle) {
	if(triangle.size() < 1) return 0;

	vector<int> last_sum(triangle[0]);
	
	vector< vector<int> >::const_iterator tri_it = triangle.begin() + 1;
	while(tri_it != triangle.end()) {
		vector<int> cur_row(*tri_it);
		
		int size = cur_row.size();
		int l_size = last_sum.size();
		for(int i = 0; i < size; i++) {
			int max = cur_row[i];
			if(i > 0)
				max += last_sum[i-1];
			if((i < l_size) && ((cur_row[i]+last_sum[i]) > max))
				max = cur_row[i]+last_sum[i];
			cur_row[i] = max;
			cout << max << " ";
		}
		cout << endl;
		last_sum = cur_row;
		tri_it++;
	}
	
	int largest = 0;
	for(vector<int>::const_iterator it = last_sum.begin(); it != last_sum.end();
			++it)
		if((*it) > largest) largest = *it;
		
	return largest;
}

vector< vector<int> > construct_triangle(ifstream &in) {
	vector< vector<int> > triangle;
	char input[10000];
	while( in.getline(input,10000) ) {
		vector<int> row;
		istringstream ss(string(input), istringstream::in);
		int val;
		while( ss >> val )
			row.push_back(val);
		if(!row.empty())
			triangle.push_back(row);
	}
	
	return triangle;
}

int main(int argc, char *argv[]) {
	ifstream triangle_file;
	triangle_file.open(argv[1]);
	vector< vector<int> > tri(construct_triangle(triangle_file));
	
	for(int i = 0; i < tri.size(); i++) {
		for(int j = 0; j < tri[i].size(); j++)
			cout << tri[i][j] << " ";
		cout << endl;
	}
	
	cout << largest_sum(tri) << endl;
	
	triangle_file.close();
	return 0;
}
