#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, q;
	cin >> n >> q;

	if (n == 1) {
		int l, r;
		while (q--) {
			cin >> l >> r;
			cout << -1 << endl;
		}
		return;
	}

	vector<int> arr(n + 1, LLONG_MIN);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> pairszero(n + 1, 0), pairsone(n + 1, 0);
	vector<int> pzero(n + 1, 0), pone(n + 1, 0);
	for (int r = 1; r <= n; r++) {
		pzero[r] += pzero[r - 1] + !arr[r];
		pone[r] += pone[r - 1] + arr[r];
	}

	for (int r = 2; r <= n; r++) {
		if (!arr[r] && !arr[r - 1] && !arr[r - 2]) {
			pairszero[r] = pairszero[r - 1];
			pairsone[r] = pairsone[r - 1];
			continue;
		}

		if (!arr[r] && !arr[r - 1]) {
			pairszero[r] = pairszero[r - 1] + 1;
			pairsone[r] = pairsone[r - 1];
			continue;
		}

		if (arr[r] == 1 && arr[r - 1] == 1 && arr[r - 2] == 1) {
			pairszero[r] = pairszero[r - 1];
			pairsone[r] = pairsone[r - 1];
			continue;
		}

		if (arr[r] == 1 && arr[r - 1] == 1) {
			pairszero[r] = pairszero[r - 1];
			pairsone[r] = pairsone[r - 1] + 1;
			continue;
		}

		pairsone[r] = pairsone[r - 1];
		pairszero[r] = pairszero[r - 1];
	}

	int l, r;
	while(q--) {
		cin >> l >> r;
		int ones = pone[r] - pone[l - 1];
		int zeroes = pzero[r] - pzero[l - 1];

		if ((ones % 3) || (zeroes % 3)) {
			cout << -1 << endl;
			continue;
		}

		int cost = 0;
		int pones = pairsone[r] - pairsone[l - 1];
		int pzeros = pairszero[r] - pairszero[l - 1];
		if (pzeros > pones) {
			int leftzero = zeroes - 3 * pzeros;
			cost += pzeros;
			cost += leftzero / 3;
			cost += ones / 3;
		} else {
			int leftone = ones - 3 * pones;
			cost += pones;
			cost += leftone / 3;
			cost += zeroes / 3;
		}

		cout << cost << endl;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) solve();
	return 0;
}