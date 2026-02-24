#include <bits/stdc++.h>
using namespace std;

#define OFFSET (int)(1e4)
#define INF (int)(1e8)

int tree[8 * OFFSET + 1];

void build(int l = 0, int r = OFFSET << 1, int idx = 1) {
	tree[idx] = -INF;
	if (l == r) return;
	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
}

int query(int elt, int l = 0, int r = OFFSET << 1, int idx = 1) {
	if (elt < l || 1 > r) return -INF;
	if (l >= 1 && r <= elt) return tree[idx];

	int m = (l + r) >> 1;
	int left = query(elt, l, m, idx << 1);
	int right = query(elt, m + 1, r, (idx << 1) | 1);
	return max(left, right);
}

void update(int i, int val, int l = 0, int r = OFFSET << 1, int idx = 1) {
	if (l == r) {
		tree[idx] = max(tree[idx], val);
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = max(tree[idx << 1], tree[(idx << 1) | 1]);
}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = (int)nums.size();
        
        vector<int> vec(n + 1);
        for (int r = 1; r <= n; r++) vec[r] = nums[r - 1];

        vector<int> dp(n + 1);
    	build();
    	dp[1] = 1, update(vec[1] + OFFSET, dp[1]);
    	int maxi = dp[1];
    	for (int r = 2; r <= n; r++)
    		dp[r] = max(1, query(vec[r] + OFFSET - 1) + 1), maxi = max(maxi, dp[r]), update(vec[r] + OFFSET, dp[r]);
        return maxi;
    }
};