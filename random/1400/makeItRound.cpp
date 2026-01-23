#include <bits/stdc++.h>
using namespace std;

#define int long long 

int calc(vector<int> &digs) {
	int pw = 1, res = 0;
	for (int r = 1; r <= 18; r++) {
		if (digs[r] == -1)
			break;
		res += digs[r] * pw;
		pw *= 10;
	}

	return res;
}

void solve() {
	int n, m;
	cin >> n >> m;

	vector<int> M(19, -1);
	vector<int> N(19, -1);

	int n1 = n, m1 = m;

	int nsz = 0, msz = 0;
	while (n1) {
		N[++nsz] = n1 % 10;
		n1 /= 10; 
	}
	while (m1) {
		M[++msz] = m1 % 10;
		m1 /= 10;
	}

	int d1, maxfinalm = M[msz];
	for (int r = 1; r <= 18; r++)
		if (N[r]) {
			d1 = N[r];
			break;
		}

	if (d1 == 2) {
		if (maxfinalm >= 5) {
			M[msz] = 5;
			for (int r = msz - 1; r >= 1; r--)
				M[r] = 0;

			cout << n * calc(M) << endl;
			return;
		}

		M[msz - 1] = 5;
		for (int r = msz - 2; r >= 1; r--)
			M[r] = 0;
		cout << n * calc(M) << endl;
	}

	if (d1 == 5) {
		if (maxfinalm >= 2) {
			M[msz] = 2;
			for (int r = msz - 1; r >= 1; r--)
				M[r] = 0;

			cout << n * calc(M) << endl;
			return;
		}

		M[msz - 1] = 5;
		for (int r = msz - 2; r >= 1; r--)
			M[r] = 0;
		cout << n * calc(M) << endl;
	}

	for (int r = msz - 1; r >= 1; r--)
		M[r] = 0;
	cout << n * calc(M) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}