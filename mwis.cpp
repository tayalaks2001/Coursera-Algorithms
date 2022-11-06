#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define INPUT_FILE "mwis_test_data.txt"
using namespace std;

int main() {
	ifstream inputFile(INPUT_FILE);
	if (inputFile.is_open()){
		int nodes;
		inputFile >> nodes;

		vector<int> weights(nodes, -1);
		for (int i=0; i<nodes; i++){
			inputFile >> weights[i];
		}

		vector<int> dp(nodes, 0);
		dp[0] = weights[0];
		dp[1] = max(weights[0], weights[1]);
		for (int i=2; i<nodes; i++){
			dp[i] = max(dp[i-1], dp[i-2] + weights[i]);
		}

		vector<bool> visited(nodes, false);
		int i = nodes-1;
		while (i >= 2){
			if (dp[i] == dp[i-1])
				i--;
			else if (dp[i] == dp[i-2] + weights[i])
				visited[i] = true, i -= 2;
		}

		if (i == 0 or dp[1] == weights[0])
			visited[0] = true;
		else if (i == 1)
			visited[1] = true;

		int targets[] = {1,2,3,4,17,117,517,997};

		for (i=0; i<8; i++){
			cout<<visited[targets[i]-1];
		}
	}
	return 0;
}