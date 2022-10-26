#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<set>
#define NODES 875714
#define INPUT_FILE "kosaraju_test_data.txt"
using namespace std;

class Graph {
public:
	int n;
	unordered_map<int,vector<int> > adjList;
	unordered_map<int, vector<int> > revAdjList;
	vector<int> finishing;
	unordered_map<int,int> scc_size;

	Graph(int nodes){
		n = nodes;
		for (int i=1; i<=n; i++){
			adjList[i] = vector<int>(0);
			revAdjList[i] = vector<int>(0);
		}
	}

	void addEdge(int from, int to){
		adjList[from].push_back(to);
		revAdjList[to].push_back(from);
	}
};

void dfsReverse(Graph &g, int start, vector<bool>& visited){
	if (visited[start])
		return;

	visited[start] = true;

	for (int nbr : g.revAdjList[start]){
		dfsReverse(g,nbr,visited);
	}
	g.finishing.push_back(start);
}

void dfsRevLoop(Graph &g){
	vector<bool> visited(NODES + 1, false);
	for (int i=NODES; i>=1; i--){
		if (!visited[i]){
			dfsReverse(g, i, visited);
		}
	}
}

void dfsForward(Graph &g, int start, vector<bool> &visited, int parent){
	if (visited[start])
		return;

	visited[start] = true;
	g.scc_size[parent] += 1;
	for (int nbr : g.adjList[start]){
		dfsForward(g,nbr,visited,parent);
	}
}

void dfsForwardLoop(Graph &g){
	vector<bool> visited(NODES + 1, false);
	int parent = 0;
	for (int i=g.finishing.size()-1; i>=0; i--){
		int node = g.finishing[i];
		if (!visited[node]){
			parent = node;
			dfsForward(g, node, visited, parent);
		}
	}
}

int main(){
	int nodes = NODES;
	Graph g(nodes);
	ifstream edgeFile(INPUT_FILE);
	if (edgeFile.is_open()){
		string from, to;
		while(edgeFile.good()){
			edgeFile>>from;
			edgeFile>>to;
			int f = stoi(from), t = stoi(to);
			g.addEdge(f,t);
		}
	}
	dfsRevLoop(g);
	dfsForwardLoop(g);
	vector<int> s;
	for (auto p : g.scc_size){
		s.push_back(p.second);
	}
	sort(s.begin(), s.end());
	auto it = s.rbegin();
	for (int i=0; i<5; i++){
		if (it == s.rend())
			break;
		cout<<*it<<" ";
		it = next(it);
	} 
	if (s.size() < 5){
		int remaining = 5-s.size();
		for (int i=0; i<remaining; i++)
			cout<<0<<" ";
	}
	return 0;
}