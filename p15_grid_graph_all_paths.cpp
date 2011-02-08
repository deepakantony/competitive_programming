#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

typedef map< int, vector<int> > Graph;

// return number of paths between start and end
long long int number_of_paths(Graph G, int start, int end) {
	vector<int> start_path;
	start_path.push_back(start);
	
	stack<int> lifo;
	lifo.push(start);
	
	long long int total_paths = 0;
	while(!lifo.empty()){
		
		int cur_vertex = lifo.top();
		lifo.pop();
		
		if(cur_vertex == end)
			total_paths++;
		else {
			vector<int> next_vertices = G[cur_vertex];
			for(int i = 0; i < next_vertices.size(); i++)  {
				if(next_vertices[i] != end)
					lifo.push(next_vertices[i]);
				else total_paths++;
			}
		}
	}
	
	return total_paths;
}

Graph construct_grid_graph(int size) {
	Graph G;
	int graph_size = size*size;
	
	// Fill the graph
	for(int row = 0; row < size; row++) 
		for(int col = 0; col < size; col++) {
			vector<int> adjacency_list;
			
			if(col < size-1)
				adjacency_list.push_back(row*size+col+1);
			if(row < size-1)
				adjacency_list.push_back((row+1)*size+col);
			G[row*size+col] = adjacency_list;
		}
	
	return G;
}



int main(int argc, char *argv[]) {
	int grid_size = atoi(argv[1]);
	Graph G = construct_grid_graph(grid_size);
	
	cout << number_of_paths(G, 0, grid_size*grid_size - 1) << endl;

	return 0;
}
