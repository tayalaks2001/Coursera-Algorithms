#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define NODES 200
#define INF 1000000
#define INPUT_FILE "dijkstra_test_data.txt"
using namespace std;

int minDistUnvisited(vector<int> distances, vector<bool> visited){
	int minm = INF, minIdx = -1;
	int nodes = distances.size();
	for (int i=1; i<=nodes; i++){
		if (distances[i-1]<minm and !visited[i-1]){
			minm = distances[i-1];
			minIdx = i;
		}
	}
	return minIdx;
}

class Graph {
public:
	int nodes;
	unordered_map<int,vector<pair<int,int> > > adjList;

	Graph(int nodes = NODES){
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

	vector<int> dijkstras(int start){
		vector<int> distances(nodes,INF);

		if (start<1 or start>nodes)
			return distances;

		distances[start-1] = 0;
		vector<bool> visited(nodes,false);
		int toExpand = minDistUnvisited(distances,visited);
		while (toExpand != -1){
			visited[toExpand-1] = true;
			for (auto p : adjList[toExpand]){
				int n = p.first, wt = p.second;
				distances[n-1] = min(distances[n-1],distances[toExpand-1] + wt);
			}
			toExpand = minDistUnvisited(distances,visited);
		}

		return distances;
	}
};

int main(){
	int a[] = { 7,37,59,82,99,115,133,165,188,197 };
	int numTargets = sizeof(a)/sizeof(int);
	vector<int> targets(a,a+numTargets);
	Graph g;
	ifstream edgeFile(INPUT_FILE);
	if (edgeFile.is_open()){
		string line;
		while (edgeFile.good()){
			getline(edgeFile, line);
			char* token = strtok((char*)line.c_str(),"\t ");
			int a = atoi(token);
			token = strtok(NULL, "\t ");
			while (token){
				int b=0,wt=0;
				int idx=0;
				while(token[idx]!='\0' and token[idx]!=',' and token[idx]!=' '){
					b = b*10 + (token[idx]-'0');
					idx++;
				}
				while(token[idx]!='\0' and (token[idx]==',' or token[idx]==' '))
					idx++;
				while(token[idx]!='\0' and token[idx]!=',' and token[idx]!=' '){
					wt = wt*10 + (token[idx]-'0');
					idx++;
				}
				g.addEdge(a,b,wt);
				token = strtok(NULL,"\t ");
			}
		}
	}
	
	vector<int> distances = g.dijkstras(1);
	for (int t : targets){
		cout<<distances[t-1]<<",";
	}

	// for (int d : distances){
	// 	cout<<d<<" ";
	// }
	// g.printAdj();
	return 0;
}