#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5 + 10)

int a[MAX + 1], b[MAX + 1];
int spf[MAX + 1];

void solve() {
	int n;
	cin >> n;

	set<int> primes;
	unordered_map<int, int> divis;
	unordered_map<int, int> rem;
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	for (int r = 1; r <= n; r++) {
		int x = a[r];
		while (x != 1) {
			int p = spf[x];
			primes.insert(p);
			while (!(x % p)) x /= p;
			divis[p]++;
		}

		x = a[r] + 1;
		while (x != 1) {
			int p = spf[x];
			primes.insert(p);
			while (!(x % p)) x /= p;
			rem[p]++;
		}
	}

	for (int p : primes) 
		if (divis[p] >= 2) {
			cout << 0 << endl;
			return;
		}
	
	for (int p : primes)
		if (divis[p] == 1 && rem[p] >= 1) {
			cout << 1 << endl;
			return;
		}

	cout << 2 << endl;
}

int32_t main() {
	int t;
	cin >> t;

	spf[0] = spf[1] = -1;
	for (int r = 2; r <= MAX; r++)
		if (!spf[r])
			for (int j = r; j <= MAX; j += r)
				spf[j] = r;
	while(t--) solve();
	return 0;
}