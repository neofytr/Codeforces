#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

int32_t main() {
	int n, c; cin >> n >> c;
	vector<int> arr(n + 2);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<pair<int, int>> v; v.push_back({0, 1});
	for (int r = 1; r <= n; r++) {
		// we can either end some previous segment at this position, or continue
		// all of the previous ones through this position

		// its optimal to choose that segment to end at this position which has the
		// minimum cost after ending

		int mini = LLONG_MAX;
		for (auto &[cost, start] : v)
			mini = min(mini, cost + (arr[start] - arr[r]) * (arr[start] - arr[r]) + c);
		v.push_back({mini, r + 1}); // the next segment starts from r + 1
		if (r == n)
			cout << mini << endl;
	}
	return 0;
}