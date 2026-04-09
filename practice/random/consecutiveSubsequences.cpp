#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++) cin >> arr[r];

    // dp[r] is the maximum length subsequence ending at element r for 1 <= r <= 1e9
    unordered_map<int, int> dp;

	int maxi = LLONG_MIN;
	int curr = -1;
	for (int r = 1; r <= n; r++) {
		int v = arr[r];
		dp[v] = dp[v - 1] + 1; // equivalent to max(dp[v], dp[v - 1] + 1)
		if (dp[v] >= maxi)
			maxi = dp[v], curr = v;
	}

	stack<int> st;
	for (int r = n; r >= 1; r--)
		if (arr[r] == curr)
			st.push(r), curr--;

	cout << maxi << endl;
	while (!st.empty())
		cout << st.top() << " ", st.pop();
	cout << endl;
    return 0;
}
