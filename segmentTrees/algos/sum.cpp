#include <bits/stdc++.h>
using namespace std;

#define int long long

// 1-indexed Segment Tree for range sum queries
class SegmentTree {
private:
    vector<int> tree;
    int n;
    
    void build(int node, int left, int right, vector<int> &arr) {
        if (left == right) {
            tree[node] = arr[left];
            return;
        }
        
        int mid = left + (right - left) / 2;
        build(2 * node, left, mid, arr);
        build(2 * node + 1, mid + 1, right, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    int query(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryRight < left || right < queryLeft) 
            return 0;
        
        
        if (queryLeft <= left && right <= queryRight) 
            return tree[node];
        
        
        int mid = left + (right - left) / 2;
        int leftSum = query(2 * node, left, mid, queryLeft, queryRight);
        int rightSum = query(2 * node + 1, mid + 1, right, queryLeft, queryRight);
        return leftSum + rightSum;
    }
    
    void update(int node, int left, int right, int pos, int val) {
        if (left == right) {
            tree[node] = val;
            return;
        }
        
        int mid = left + (right - left) / 2;
        if (pos <= mid) 
            update(2 * node, left, mid, pos, val);
        else 
            update(2 * node + 1, mid + 1, right, pos, val);
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
public:
    SegmentTree(int size, vector<int>& input) {
        n = size;
        tree.resize(4 * n + 1, 0);
        build(1, 1, n, input);
    }
    
    int sum(int l, int r) {
        return query(1, 1, n, l, r);
    }
    
    void set(int idx, int val) {
        update(1, 1, n, idx, val);
    }
};

int32_t main() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	SegmentTree s(n, arr);
	cout << s.sum(1, n) << endl;
	cout << s.sum(2, n - 1) << endl;
	s.set(1, 10);
	cout << s.sum(1, n) << endl;
	return 0;
}