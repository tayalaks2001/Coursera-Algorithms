#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define NUM_CLUSTERS 4
#define INPUT_FILE_SMALL "clustering_test_data_small.txt"
#define INPUT_FILE_LARGE "clustering_test_data_large.txt"
using namespace std;

class edge {
public:
	int a, b, wt;

	edge(){
		a = b = wt = 0;
	};

	edge(int a, int b, int wt){
		this->a = a;
		this->b = b;
		this->wt = wt;
	}
};

bool myComp(edge e1, edge e2){
	if (e1.wt == e2.wt){
		return e1.a < e2.a;
	}

	return e1.wt < e2.wt;
}

class union_find {
public:
	int nodes;
	vector<int> parent;

	union_find(int nodes){
		this->nodes = nodes;
		parent = vector<int>(nodes+1, -1);
	}

	int find(int n){
		if (n<1 or n>nodes){
			cout<<"Trying to find out of range!"<<endl;
			return INT_MIN;
		}

		if (parent[n] == -1){
			return n;
		}

		return parent[n] = find(parent[n]);
	}

	bool union_set(int n1, int n2){
		int p1 = find(n1), p2 = find(n2);

		if (p1 != p2){
			parent[p2] = p1;
			return true;
		}

		return false;
	}
};

int main() {
	ifstream edgeFile(INPUT_FILE_SMALL);

	int nodes;
	vector<edge> edges;
	vector<vector<int> > adjMatrix;

	if (edgeFile.is_open()){
		string line;
		getline(edgeFile, line);
		nodes = stoi(line);
		adjMatrix = vector<vector<int> >(nodes+1, vector<int>(nodes+1,-1));

		while (edgeFile.good()){
			int a,b,wt;
			getline(edgeFile, line);
			char *temp = strtok((char*)line.c_str(), " ");
			a = atoi(temp);
			temp = strtok(NULL, " ");
			b = atoi(temp);
			temp = strtok(NULL, " ");
			wt = atoi(temp);
			edges.push_back(edge(a,b,wt));
			adjMatrix[a][b] = wt;

		}
	}

	sort(edges.begin(), edges.end(), myComp);
	int clusters = nodes, idx = 0;
	union_find uf(nodes);
	while (clusters > NUM_CLUSTERS and idx < edges.size()){
		if (uf.union_set(edges[idx].a, edges[idx].b))
			clusters--;
		idx++;
	}

	int spacing = INT_MAX;
	for (int i=1; i<=nodes; i++){
		for (int j=i+1; j<=nodes; j++){
			if (uf.find(i) != uf.find(j)){
				spacing = min(spacing, adjMatrix[i][j]);
			}
		}
	}
	cout<<spacing<<endl;
	return 0;
}