#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	map<tuple<int, int, int>, int> cnt;
	for (int j = 1; j <= n - 2; j++) {
		int a = arr[j], b = arr[j + 1], c = arr[j + 2];
		cnt[{a, b, c}]++;
	}

	map<pair<int, int>, int> leftsum;
	map<pair<int, int>, int> leftsumsq;
	map<pair<int, int>, int> midsum;
	map<pair<int, int>, int> midsumsq;
	map<pair<int, int>, int> rightsum;
	map<pair<int, int>, int> rightsumsq;
	map<tuple<int, int, int>, bool> done;
	for (int j = 1; j <= n - 2; j++) {
		int a = arr[j], b = arr[j + 1], c = arr[j + 2];
		if (!done[{a, b, c}]) {
			leftsum[{b, c}] += cnt[{a, b, c}];
			leftsumsq[{b, c}] += cnt[{a, b, c}] * cnt[{a, b, c}];

			midsum[{a, c}] += cnt[{a, b, c}];
			midsumsq[{a, c}] += cnt[{a, b, c}] * cnt[{a, b, c}];

			rightsum[{a, b}] += cnt[{a, b, c}];
			rightsumsq[{a, b}] += cnt[{a, b, c}] * cnt[{a, b, c}];
			done[{a, b, c}] = true;
		}
	}


	int res = 0;
	map<pair<int, int>, bool> leftDone;
	map<pair<int, int>, bool> midDone;
	map<pair<int, int>, bool> rightDone;
	for (int j = 1; j <= n - 2; j++) {
		int a = arr[j], b = arr[j + 1], c = arr[j + 2];
		if (!leftDone[{b, c}]) {
			leftDone[{b, c}] = true;
			int sum = leftsum[{b, c}], sq = leftsumsq[{b, c}];
			res += ((sum * sum - sq) / 2);
		}	

		if (!midDone[{a, c}]) {
			midDone[{a, c}] = true;
			int sum = midsum[{a, c}], sq = midsumsq[{a, c}];
			res += ((sum * sum - sq) / 2);
		}

		if (!rightDone[{a, b}]) {
			rightDone[{a, b}] = true;
			int sum = rightsum[{a, b}], sq = rightsumsq[{a, b}];
			res += ((sum * sum - sq) / 2);
		}
	}

	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int r = 1; r <= t; r++) solve(r);
	return 0;
}