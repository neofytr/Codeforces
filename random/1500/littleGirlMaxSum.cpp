#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, q; cin >> n >> q;
	vector<int> a(n + 1), p(n + 2, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];


	int l, r;  
	while (q--) {
		cin >> l >> r;
		p[l] += 1, p[r + 1] -= 1;
	}

	for (int i = 1; i <= n; i++) p[i] += p[i - 1];

	sort(p.begin() + 1, p.end() - 1);
	sort(a.begin() + 1, a.end());


	int res = 0;
	for (int i = 1; i <= n; i++)
		res += a[i] * p[i];
	cout << res << endl;
	return 0;
}