#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 2);
	for (int r = 1; r <= n; r++) cin >> a[r];

	vector<int> rdp(n + 2, 0), ldp(n + 2, 0);
	rdp[1] = 1;
	int maxi = 1;
	for (int i = 2; i <= n; i++) {
		rdp[i] = 1;
		if (a[i] > a[i - 1]) rdp[i] = max(rdp[i], rdp[i - 1] + 1);
		maxi = max(maxi, rdp[i]);
	}

	ldp[n] = 1;
	for (int i = n - 1; i >= 1; i--) {
		ldp[i] = 1;
		if (a[i] < a[i + 1]) ldp[i] = max(ldp[i], ldp[i + 1] + 1);
	}

	a[0] = LLONG_MIN;
	a[n + 1] = LLONG_MAX;
	for (int i = 1; i <= n; i++) {
		// remove a[i]
		if (a[i - 1] < a[i + 1])
			maxi = max(maxi, rdp[i - 1] + ldp[i + 1]);
	}

	cout << maxi << endl;
	return 0;
}