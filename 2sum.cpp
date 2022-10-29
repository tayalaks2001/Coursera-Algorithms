#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<climits>
#include<unordered_set>
#include<unordered_map>
#define INPUT_FILE "2sum_test_data.txt"
#define int long long
using namespace std;

int strToInt(string val){
	int answer = 0, i = 0, n = val.size();
	bool neg = false;

	if (val[0] == '-'){
		neg = true;
		i += 1;
	}
	while (i < n){
		answer = answer*10 + (val[i]-'0');
		i++;
	}
	if (neg)
		answer *= -1;
	return answer;
}

int32_t main(){
	vector<int> A;
	ifstream infile(INPUT_FILE);
	int lower = -10000, upper = 10000;
	if (infile.is_open()){
		int curr;
		while (infile.good()){
			infile>>curr;
			A.push_back(curr);
		}
		sort(A.begin(), A.end());
		// int cnt = 0;
		// for (int t=-10000; t<=10000; t++){
		// 	for (int x : A){
		// 		int target = t-x;
		// 		if (target != x and A.find(target) != A.end()){
		// 			cout<<"found: "<<t<<"; "<<x<<" "<<target<<endl;
		// 			cnt++;
		// 			break;
		// 		}
		// 	}
		// }

		// cout<<cnt<<endl;
		int i = 0;
	    int j = A.size()-1;
	    int count = 0;
	    unordered_map<int, bool> sumList;
	    while (i < j) {
	        if (A[i] + A[j] < lower) i++;
	        else if (A[i] + A[j] > upper) j--;
	        else {
	            for (int pos = i+1; pos <= j; pos++) {
	                int sum = A[i] + A[pos];
	                if (sum > upper) break;
	                else if (A[i] != A[pos] && sum >= lower) {
	                    if (sumList[sum] == 0) {
	                        count++;
	                        sumList[sum] = 1;
	                        cout << "sum is " << A[i] << "+" << A[pos] << "=" << sum << endl;
	                    }
	                }
	            }
	            i++;
	        }
	    }

	    cout<<count;
	}
	return 0;
}