/*
  Problem: The Necklace 
  Link: http://uva.onlinejudge.org/external/100/10054.html
  Author: Deepak Antony
*/

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;
import java.io.IOException;

class Pair {
	public Pair(int first, int second) {
		this.first = first;
		this.second = second;
	}
	public int first = 0;
	public int second = 0;
}


class Main 
{
	// Check if the graph is eulerian; i.e. even degree for each vertex
	public static boolean isEulerian(ArrayList<ArrayList<Pair>> G) {
		for(ArrayList<Pair> item : G) 
			if(item.size() % 2 != 0) return false;
		return true;
	}

	// Find the euler path
	public static void eulerPath(
		ArrayList<ArrayList<Pair>> G, ListIterator<Integer> path, int u) {
		for(Pair v : G.get(u)) {
			if(v.second == 1) {
				v.second = 0;
				// remove the bidirectional edge
				for(Pair vu : G.get(v.first))
					if(vu.second == 1 && vu.first == u) {
						vu.second = 0;
						break;
					}
				path.add(u);
				eulerPath(G, path, v.first);
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader inp = 
			new BufferedReader(new InputStreamReader(System.in));

		ArrayList<ArrayList<Pair>> G;
		
		int T = Integer.parseInt(inp.readLine());
		int startVertex = 0;
		int graphSize = 50;
		for(int test = 0; test < T; ++test) {
			int numberOfEdges = Integer.parseInt(inp.readLine());
			G = new ArrayList<ArrayList<Pair>>();
			for(int index = 0; index < graphSize; ++index)
				G.add(new ArrayList<Pair>());
			for(int edge = 0; edge < numberOfEdges; ++edge) {
				String[] tokens = inp.readLine().split("\\s");
				int u = Integer.parseInt(tokens[0]); --u;
				int v = Integer.parseInt(tokens[1]); --v;
				startVertex = u;
				G.get(u).add(new Pair(v, 1)); G.get(v).add(new Pair(u,1));
			}
			System.out.println("Case #"+(test+1));
			if(isEulerian(G)) {
				LinkedList<Integer> path = new LinkedList<Integer>();
				eulerPath(G, path.listIterator(), startVertex);
				for(int index = 0; index < path.size()-1; ++index)
					System.out.println(
						(path.get(index)+1) + " " + (path.get(index+1)+1));
				if(path.size() > 0)
					System.out.println(
						(path.get(path.size()-1)+1) + " " + (path.get(0) + 1));
			}
			else System.out.println("some beads may be lost");
			if(test != T-1) System.out.println();
		}
	}
}
