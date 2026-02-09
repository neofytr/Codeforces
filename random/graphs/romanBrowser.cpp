#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, k; cin >> n >> k;
	vector<int> tab(n + 1);
	for (int r = 1; r <= n; r++) cin >> tab[r];

	int maxi = LLONG_MIN;
	for (int b = 0; b < k; b++) {
		int e = 0, s = 0;
		for (int r = 1; r <= n; r++)
			if (r >= b && !((r - b) % k))
				continue;
			else if (tab[r] == 1) e++;
			else s++;
		maxi = max(maxi, llabs(e - s));
	}
	cout << maxi << endl;
	return 0;
}