#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

int32_t main() {
	int n, c; cin >> n >> c;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<pair<int, int>> dq; dq.push_back({0, arr[1]});
	for (int r = 2; r <= n; r++) {
		int mini = INF;
		for (auto [cost, start] : dq) 
			mini = min(mini, cost + (arr[r - 1]  - start) * (arr[r - 1] - start) + c);
		dq.push_back({mini, arr[r]});
		cout << mini << endl;
	}
			
	return 0;
}