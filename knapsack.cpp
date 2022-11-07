#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define int long long
#define INPUT_FILE "knapsack_test_data_small.txt"
using namespace std;

int32_t main() {
	ifstream inputFile(INPUT_FILE);

	if (inputFile.is_open()){
		int W, n;
		inputFile >> W >> n;

		cout<<"capacity: "<<W<<" num_items: "<<n<<endl;
		vector<int> weights(n);
		vector<int> values(n);
		for (int i=0; i<n; i++){
			inputFile >> values[i] >> weights[i];
		}
		cout<<"objects:"<<endl;
		for (int i=0; i<n; i++){
			cout<<values[i]<<" "<<weights[i]<<endl;
		}
		cout<<endl;

		vector<vector<int> > dp(n+1, vector<int>(W+1,0));

		for (int i=1; i<=n; i++){
			for (int j=0; j<=W; j++){
				if (j < weights[i-1])
					dp[i][j] = dp[i-1][j];
				else
					dp[i][j] = max(dp[i-1][j], dp[i-1][j-weights[i-1]]+values[i-1]);
			}
		}

		cout<<dp[n][W];
	}
	return 0;
}