#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<unordered_map>
#define int long long
#define INPUT_FILE "huffman_test_data.txt"
using namespace std;

class node {
public:
	int wt;
	node *left, *right;

	node(int wt = 0){
		this->wt = wt;
		left = right = NULL;
	} 
};

class minHeap {
public:
	vector<node*> v;
	int size, capacity;

	minHeap(int cap = 0){
		capacity = cap, size = 0;
		v = vector<node*>(capacity);
	}

	int parent(int i){
		return (i-1)/2;
	}

	int left(int i){
		return 2*i + 1;
	}

	int right(int i){
		return 2*i + 2;
	}

	void insert(node* n){
		if (size == capacity){
			cout<<"trying to insert on full heap"<<endl;
			return;
		}

		size++;
		v[size-1] = n;
		int i = size-1;
		while (i > 0 and v[parent(i)]->wt >= v[i]->wt){
			swap(v[i], v[parent(i)]);
			i = parent(i);
		}
	}

	void heapify(int i){
		int l = left(i), r = right(i);
		int smallest = i;

		if (l < size and v[l]->wt < v[i]->wt)
			smallest = l;
		if (r < size and v[r]->wt < v[smallest]->wt)
			smallest = r;

		if (smallest != i){
			swap(v[i], v[smallest]);
			heapify(smallest);
		}
	}

	node* extractMin(){
		node* ans = v[0];
		swap(v[size-1], v[0]);
		size--;
		heapify(0);
		return ans;
	}
};

void getDepths(node* root, int d, int &minm, int &maxm){
	if (root->left==NULL and root->right==NULL){
		minm = min(minm, d);
		maxm = max(maxm, d);
		return;
	}

	getDepths(root->left, d+1, minm, maxm);
	getDepths(root->right, d+1, minm, maxm);
}

int32_t main() {
	ifstream inputFile(INPUT_FILE);

	if (inputFile.is_open()){
		int nodes;
		inputFile >> nodes;
		minHeap mh(nodes);
		int weight;
		while (inputFile >> weight){
			node* temp = new node(weight);
			mh.insert(temp);
		}

		while (mh.size > 1){
			node* min1 = mh.extractMin();
			node* min2 = mh.extractMin();

			node* combo = new node(min1->wt + min2->wt);
			combo->left = min1;
			combo->right = min2;
			mh.insert(combo);
		}

		int minm = INT_MAX, maxm = INT_MIN;
		node* root = mh.v[0];
		getDepths(root, 0, minm, maxm);
		cout<<minm<<" "<<maxm<<endl;
	}

	return 0;
}