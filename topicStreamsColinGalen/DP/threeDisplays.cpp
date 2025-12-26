#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	vector<int> s(n + 1), c(n + 1);
	for (int r = 1; r <= n; r++) cin >> s[r];
	for (int r = 1; r <= n; r++) cin >> c[r];

	int mincost = LLONG_MAX;
	for (int j = 2; j <= n - 1; j++) {
		int c1 = LLONG_MAX, c2 = LLONG_MAX;
		for (int i = 1; i < j; i++)
			if (s[i] < s[j])
				c1 = min(c1, c[i]);
		for (int k = j + 1; k <= n; k++)
			if (s[k] > s[j])
				c2 = min(c2, c[k]);

		if (c1 != LLONG_MAX && c2 != LLONG_MAX)
			mincost = min(mincost, c1 + c2 + c[j]);
	}

	cout << (mincost == LLONG_MAX ? -1 : mincost) << endl;
}