#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, K;
	long long X;
	cin >> N >> K >> X;

	vector<long long> A(N);
	for (int i = 0; i < N; i++) cin >> A[i];

	sort(A.begin(), A.end(), greater<long long>());

	vector<long long> pref(N + 1, 0);
	for (int i = 0; i < N; i++) {
		pref[i + 1] = pref[i] + A[i];
	}

	for (int m = 1; m <= N; m++) {
		int t = max(0LL, m - (N - K));  
		if (t == 0) continue;

		long long worst =
			pref[m] - pref[m - t];

		if (worst >= X) {
			cout << m << "\n";
			return 0;
		}
	}

	cout << -1 << "\n";
	return 0;
}
