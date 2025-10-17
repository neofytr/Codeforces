#include <bits/stdc++.h>
using namespace std;

#define int long long 

int nrem(int x, int r) {
	if (!r)
		if (x < 5)
			return 0;
		else 
			return ((x - 5) / 5 + 1);

	if (x < r)
		return 0;
	return (x - r) / 5 + 1;
}

int32_t main() {
	int n, m;
	cin >> n >> m;

	int ans = nrem(n, 0) * nrem(m, 0) + nrem(n, 1) * nrem(m, 4) + nrem(n, 4) * nrem(m, 1) + nrem(n, 2) * nrem(m, 3) + nrem(n, 3) * nrem(m, 2);
	cout << ans << endl;
	return 0;
}