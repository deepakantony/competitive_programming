/*
  Problem: Fire Escape Routes
  Link: http://www.codechef.com/MARCH13/problems/FIRESC
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Connected components; multiply the count of each components
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

#define MODULO_NUM 1000000007

int number_of_nodes_in_component(
	VVI &graph, VI &node_label_array, int cur_node_index
	)
{
	int n_nodes_in_cur_component = 1;
	int node_index;

	node_label_array[cur_node_index] = 1;
	
	REP(node_index, graph[cur_node_index].size())
	{
		if(node_label_array[graph[cur_node_index][node_index]] == 0)
		{
			n_nodes_in_cur_component += 
				number_of_nodes_in_component(
					graph, node_label_array, graph[cur_node_index][node_index]
					);
		}
	}

	return n_nodes_in_cur_component;
}

PII number_of_connected_components(VVI &graph)
{
	int n_connected_components = 0;
	LL n_node_combinations = 1;
	int n_final_result_node_combinations;
	int n_nodes_in_component;
	int node_index;
	VI node_label_array(graph.size(), 0);

	REP(node_index, graph.size())
	{
		if(node_label_array[node_index] == 0)
		{
			++n_connected_components;

			n_nodes_in_component = 
				number_of_nodes_in_component(
					graph, node_label_array, node_index);

			n_node_combinations = 
				(n_nodes_in_component * n_node_combinations) % MODULO_NUM;
		}
	}

	n_final_result_node_combinations = (int)n_node_combinations;

	return mp(n_connected_components, n_final_result_node_combinations);
}

void solve_fire_escape_routes()
{
	int number_of_tests;
	scanf("%d", &number_of_tests);

	int test_index;
	int number_of_nodes, number_of_edges;
	int node_1, node_2, node_index;
	REP(test_index, number_of_tests)
	{
		scanf("%d%d", &number_of_nodes, &number_of_edges);

		VVI graph(number_of_nodes);
		
		REP(node_index, number_of_edges)
		{
			scanf("%d%d", &node_1, &node_2);
			--node_1;
			--node_2;

			graph[node_1].push_back(node_2);
		}

		PII component_combination_pair = number_of_connected_components(graph);
		printf("%d %d\n", 
			   component_combination_pair.first,
			   component_combination_pair.second);
	}

}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
//	if(argc == 2)
//		freopen(argv[1], "r", stdin);
#endif 
	solve_fire_escape_routes();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
