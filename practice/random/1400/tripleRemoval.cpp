#include <bits/stdc++.h>
using namespace std;

const int MAX = 250010;

int A[MAX];

int diff[MAX];
int diffsum[MAX];

int sum[2][MAX];

void solve() {
	int N, Q;
	cin >> N >> Q;
	int i;
	for (i = 1; i <= N; i++) cin >> A[i];
	for (i = 1; i <= N; i++) {
		sum[0][i] = sum[0][i - 1];
		sum[1][i] = sum[1][i - 1];
		sum[A[i]][i]++;

		diff[i] = A[i] != A[i - 1];
		diffsum[i] = diffsum[i - 1] + diff[i];
	}
	int l, r;
	for (i = 1; i <= Q; i++) {
		cin >> l >> r;

		int z, o;
		z = sum[0][r] - sum[0][l - 1];
		o = sum[1][r] - sum[1][l - 1];
		if (z % 3) {
			cout << -1 << '\n';
			continue;
		}
		if (o % 3) {
			cout << -1 << '\n';
			continue;
		}

		int sum = z / 3 + o / 3;
		if (diffsum[r] - diffsum[l] == (r - l)) sum++;
		cout << sum << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t, T;
	cin >> T;
	for (t = 1; t <= T; t++) solve();
}