#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> matmul(vector<vector<int>> &a, vector<vector<int>> &b) {
	int n = a.size();
	vector<vector<int>> res(n, vector<int>(n));

	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++) {
			res[r][c] = 0;
			for (int k = 0; k < n; k++)
				res[r][c] += a[r][k] * b[k][c];
		}

	return res;
}

vector<vector<int>> pow(vector<vector<int>> base, int exp) {
	vector<vector<int>> res = {{1, 0}, {0, 1}};

	while (exp) {
		if (exp & 1) res = matmul(res, base);
		base = matmul(base, base);
		exp >>= 1;
	}

	return res;
}

void solve() {
	int n, k; cin >> n >> k;

	if (k == 1) {
		cout << 1 << endl;
		return;
	}

	int a = 0, b = 1;
	int kmax = -1;

	for (int i = 3; i <= 100; i++) {
		int c = a + b;
		if (c > n) {
			kmax = i;
			break;
		}
		a = b;
		b = c;
	}

	if (kmax == -1 || k > kmax) {
		cout << 0 << endl;
		return;
	}

	vector<vector<int>> T = {{1, 1}, {1, 0}};
	T = pow(T, k - 2);

	a = T[0][0]; // Fk
	b = T[0][1]; // F(k-1)

	int cnt = 0;
	for (int f1 = 0; f1 <= n; f1++) {
		int rem = n - b * f1;
		if (rem >= 0 && !(rem % a) && rem / a >= f1)
			cnt++;
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}