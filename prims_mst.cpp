#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define INPUT_FILE "prims_mst_test_data.txt"
using namespace std;

class Graph {
public:
	int nodes;
	unordered_map<int,vector<pair<int,int> > > adjList;

	Graph(int nodes = 0){
		this->nodes = nodes;
	}

	void addEdge(int a, int b, int wt){
		adjList[a].push_back(make_pair(b,wt));
		adjList[b].push_back(make_pair(a,wt));
	}

	void printAdj(){
		for (auto p : adjList){
			cout<<p.first<<": ";
			for (auto pi : p.second){
				cout<<pi.first<<","<<pi.second<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
};

int getMinIdx(vector<int> distance, vector<bool> visited){
	int minIdx = 0;
	for (int i=1; i<distance.size(); i++){
		if (!visited[i] and distance[i] < distance[minIdx])
			minIdx = i;
	}
	return minIdx;
}

int totalMSTCost(Graph g){
	long long int result = 0;

	int n = g.nodes;
	vector<int> distance(n+1, INT_MAX);
	vector<bool> visited(n+1, false);

	distance[1] = 0;

	int minIdx = getMinIdx(distance, visited);
	while (minIdx != 0){
		visited[minIdx] = true;
		result += distance[minIdx];
		for (auto p : g.adjList[minIdx]){
			distance[p.first] = min(distance[p.first], p.second);
		}
		minIdx = getMinIdx(distance, visited);
	}

	return result;
}

int main() {
	ifstream edgeFile(INPUT_FILE);
	Graph g;

	if (edgeFile.is_open()){
		char* temp;
		string line;

		int nodes, edges;
		getline(edgeFile, line);
		temp = strtok((char*)line.c_str(), " ");
		nodes = atoi(temp);
		temp = strtok(NULL, " ");
		edges = atoi(temp);

		g.nodes = nodes;
		while (edgeFile.good()){
			getline(edgeFile, line);
			int a,b,wt;
			temp = strtok((char*)line.c_str(), " ");
			a = atoi(temp);
			temp = strtok(NULL, " ");
			b = atoi(temp);
			temp = strtok(NULL, " ");
			wt = atoi(temp);

			g.addEdge(a,b,wt);
		}
	}

	cout<<totalMSTCost(g)<<endl;
	return 0;
}