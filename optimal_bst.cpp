#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<climits>
#include<unordered_map>
#define int double
using namespace std;

int32_t main(){
	int weights[] = {0.2,0.05,0.17,0.1,0.2,0.03,0.25};
	int size = sizeof(weights)/sizeof(int);
	for (int32_t i=1; i<size; i++)
		weights[i] += weights[i-1];

	vector<vector<int> > dp(size, vector<int>(size,INT_MAX));
	for (int32_t sz=0; sz<size; sz++){
		for (int32_t start=0; start<size-sz; start++){
			int pr = weights[start+sz];
			if (start > 0)
				pr -= weights[start-1];

			for (int i=start; i<=start+sz; i++){
				int l=0, r=0;
				if (i > start)
					l = dp[start][i-1];
				if (i < start+sz)
					r = dp[i+1][start+sz];

				dp[start][start+sz] = min(dp[start][start+sz], l+r+pr);
			}
		}
	}

	cout<<dp[0][size-1];
	return 0;
}