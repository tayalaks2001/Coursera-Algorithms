#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define INPUT_FILE "greedy_jobs_test_data.txt"
using namespace std;

bool comp1(pair<int,int> p1, pair<int,int> p2) {
	int diff1 = p1.first-p1.second, diff2 = p2.first-p2.second;
	if (diff1 == diff2){
		return p1.first > p2.first;
	}
	return diff1 > diff2;
}

bool comp2(pair<int,int> p1, pair<int,int> p2) {
	double ratio1 = ((double)p1.first)/((double)p1.second);
	double ratio2 = ((double)p2.first)/((double)p2.second);
	if (ratio1 == ratio2){
		return p1.first > p2.first;
	}
	return ratio1 > ratio2;
}

int main() {
	int NUM_JOBS;
	vector<pair<int,int> > jobs;
	ifstream jobFile(INPUT_FILE);
	if (jobFile.is_open()){
		string line;
		getline(jobFile, line);
		NUM_JOBS = stoi(line);
		while (jobFile.good()){
			getline(jobFile, line);
			char* temp1 = strtok((char*)line.c_str(), " ");
			char* temp2 = strtok(NULL, " ");
			int wt = atoi(temp1), len = atoi(temp2);
			jobs.push_back(make_pair(wt, len));
		}
	}

	if (jobs.size() != NUM_JOBS){
		cout<<"DATA INPUT DOESN'T MATCH SIZE!"<<endl;
		return 0;
	}

	sort(jobs.begin(), jobs.end(), comp2);

	long long int time = 0, result = 0;
	for (int i=0; i<NUM_JOBS; i++){
		time += jobs[i].second;
		result += jobs[i].first * time;
	}
	cout<<result<<endl;
	return 0;
}