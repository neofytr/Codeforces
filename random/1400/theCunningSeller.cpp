#include <bits/stdc++.h>
using namespace std;

#define int long long

int pw(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1) res = res * base;
		base = base * base;
		exp >>= 1;
	}
	return res;
}


void solve() {
	int n, k; cin >> n >> k;

	int left = 0;
	int right = 19;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (pw(3, mid) <= n) left = mid;
		else right = mid;
	}

	int x = n;
	vector<int> coeffs(left + 1, 0);
	for (int i = left; i >= 0; i--) 
		for (int d = 2; d >= 0; d--)
			if (d * pw(3, i) <= x) {
				coeffs[i] = d; 
				x -= d * pw(3, i);
				break;
			}
	
	int cnt = 0;
	for (int r = 0; r <= left; r++) cnt += coeffs[r];
	if (cnt > k) {
		cout << -1 << endl;
		return;
	}

	for (int r = left; r >= 1; r--) {
		// 2 * d + cnt <= k
		// d <= (k - cnt) / 2
		int d = min(coeffs[r], (k - cnt) / 2);
		coeffs[r - 1] += 3 * d;
		coeffs[r] -= d;
		cnt += 2 * d;
	}

	int cost = coeffs[0] * pw(3, 1);
	for (int r = 1; r <= left; r++)
		cost += coeffs[r] * (pw(3, r + 1) + r * pw(3, r - 1));
	cout << cost << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}