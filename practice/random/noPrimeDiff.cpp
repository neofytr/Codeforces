#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1000)

vector<bool> nprime(MAX + 1);

void solve() {
	int n, m; cin >> n >> m;
}

int32_t main() {
	nprime[0] = nprime[1] = true;
	for (int i = 2; i <= MAX; i++)
		if (!nprime[i])
			for (int j = i * i; j <= MAX; j++)
				nprime[j] = true;
	int t; cin >> t;
	while (t--) solve();
	return 0;
}