#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define int long long
#define INPUT_FILE "knapsack_test_data_big.txt"
using namespace std;

int32_t main() {
	ifstream inputFile(INPUT_FILE);

	if (inputFile.is_open()){
		int W, n;
		inputFile >> W >> n;

		vector<int> weights(n);
		vector<int> values(n);
		for (int i=0; i<n; i++){
			inputFile >> values[i] >> weights[i];
		}

		vector<int> prev(W+1, 0);
		vector<int> curr(W+1, 0);
		for (int i=1; i<=n; i++){
			for (int j=0; j<=W; j++){
				if (j < weights[i-1])
					curr[j] = prev[j];
				else
					curr[j] = max(prev[j], prev[j-weights[i-1]]+values[i-1]);
			}
			prev = curr;
		}

		cout<<curr[W];
	}
	return 0;
}