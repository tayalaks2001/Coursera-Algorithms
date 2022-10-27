#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<climits>
#include<unordered_map>
#define INPUT_FILE "median_test_data.txt"
#define N 10000
using namespace std;

class minHeap {
public:
	vector<int> arr;
	int sz, cap;

	minHeap(int cap = N){
		this->cap = cap;
		arr = vector<int>(cap,0);
		sz = 0;
	}

	int parent(int idx){
		return (idx-1)/2;
	}

	int left(int idx){
		return 2*idx + 1;
	}

	int right(int idx){
		return 2*idx + 2;
	}

	void minHeapify(int idx){
		int smallest = idx;
		int l = left(idx), r = right(idx);
		if (l < sz and arr[l] < arr[idx])
			smallest = l;
		if (r < sz and arr[r] < arr[smallest])
			smallest = r;

		if (smallest != idx){
			swap(arr[idx], arr[smallest]);
			minHeapify(smallest);
		}
	}

	void insert(int val){
		if (sz == cap){
			return;
		}

		arr[sz] = val;
		sz++;
		int i = sz-1;
		while (i > 0 and arr[parent(i)] > arr[i]){
			swap(arr[parent(i)], arr[i]);
			i = parent(i);
		}
	}

	int extractMin(){
		if (sz == 0)
			return -1;

		int minm = arr[0];
		arr[0] = arr[sz-1];
		sz--;
		if (sz > 1){
			minHeapify(0);
		}
		return minm;
	}

	int getMin(){
		if (sz == 0)
			return INT_MAX;

		return arr[0];
	}
};


class maxHeap {
public:
	vector<int> arr;
	int sz, cap;

	maxHeap(int cap = N){
		this->cap = cap;
		arr = vector<int>(cap,0);
		sz = 0;
	}

	int parent(int idx){
		return (idx-1)/2;
	}

	int left(int idx){
		return 2*idx + 1;
	}

	int right(int idx){
		return 2*idx + 2;
	}

	void maxHeapify(int idx){
		int largest = idx;
		int l = left(idx), r = right(idx);
		if (l < sz and arr[l] > arr[idx])
			largest = l;
		if (r < sz and arr[r] > arr[largest])
			largest = r;

		if (largest != idx){
			swap(arr[idx], arr[largest]);
			maxHeapify(largest);
		}
	}

	void insert(int val){
		if (sz == cap){
			return;
		}

		arr[sz] = val;
		sz++;
		int i = sz-1;
		while (i > 0 and arr[parent(i)] < arr[i]){
			swap(arr[parent(i)], arr[i]);
			i = parent(i);
		}
	}

	int extractMax(){
		if (sz == 0)
			return -1;

		int maxm = arr[0];
		arr[0] = arr[sz-1];
		sz--;
		if (sz > 1){
			maxHeapify(0);
		}
		return maxm;
	}

	int getMax(){
		if (sz == 0)
			return INT_MIN;

		return arr[0];
	}
};


class medianCalculator {
public:
	minHeap upper;
	maxHeap lower;

	medianCalculator(){;}

	int insertAndGetMedian(int val){
		int lowerMax = lower.getMax();
		int upperMin = upper.getMin();

		int totalSz = lower.sz + upper.sz + 1;
		if (val <= upperMin){
			lower.insert(val);
			if (lower.sz - upper.sz > (totalSz%2)){
				int removed = lower.extractMax();
				upper.insert(removed);
			}
		}
		else{
			upper.insert(val);
			if (upper.sz > lower.sz){
				int removed = upper.extractMin();
				lower.insert(removed);
			}
		}

		return lower.getMax();
	}
};

int main(){
	ifstream infile(INPUT_FILE);
	if (infile.is_open()){
		medianCalculator mc;
		int sum = 0;
		string curr;
		while (infile.good()){
			infile>>curr;
			int median = mc.insertAndGetMedian(stoi(curr));
			sum = (sum + median) % N;
		}
		cout<<sum;
	}
	return 0;
}