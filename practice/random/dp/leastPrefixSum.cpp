#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int cnt = 0;

	priority_queue<int> pq;
	int current_suffix_sum = 0;

	for (int i = m; i >= 2; i--) {
		current_suffix_sum += arr[i];

		if (arr[i] > 0) {
			pq.push(arr[i]);
		}

		while (current_suffix_sum > 0) {
			int largest = pq.top();
			pq.pop();
			current_suffix_sum -= 2 * largest;
			cnt++;
		}
	}

	int s = 0;
	priority_queue<int, vector<int>, greater<int>> min_pq;

	for (int r = m + 1; r <= n; r++) {
		s += arr[r];
		if (arr[r] < 0) min_pq.push(arr[r]);

		while (s < 0) {
			auto elt = min_pq.top();
			min_pq.pop();
			s -= 2 * elt;
			cnt++;
		}
	}

	cout << cnt << endl;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
