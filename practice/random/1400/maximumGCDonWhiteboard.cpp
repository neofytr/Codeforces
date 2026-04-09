#include <bits/stdc++.h>
using namespace std;

#define int long long

// gets the index of the last element <= x
int last(int x, vector<int> &arr) {
	auto itr = upper_bound(arr.begin() + 1, arr.end(), x);
	if (itr == arr.begin() + 1) return -1;
	return itr - arr.begin() - 1;
}

int first(int x, vector<int> &arr) {
	auto itr = lower_bound(arr.begin() + 1, arr.end(), x);
	if (itr == arr.end()) return -1;
	return itr - arr.begin();
}

void solve() {
	int n, k; cin >> n >> k;
	vector<int> arr(n + 1, LLONG_MIN);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr.begin() + 1, arr.end());
	for (int g = n; g >= 2; g--) {
		int cnt = 0;
		int l = last(g - 1, arr);
		if (l != -1) cnt += l;
		l = first(g + 1, arr);
		if (l != -1) {
			int r = last(2 * g - 1, arr);
			if (r != -1) cnt += (r - l + 1);
		}

		l = first(2 * g + 1, arr);
		if (l != -1) {
			int r = last(3 * g - 1, arr);
			if (r != -1) cnt += (r - l + 1);
		}

		l = first(3 * g + 1, arr);
		if (l != -1) {
			int r = last(4 * g - 1, arr);
			if (r != -1) cnt += (r - l + 1);
		}

		if (cnt <= k) {
			cout << g << endl;
			return;
		}
	}
	cout << 1 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
}