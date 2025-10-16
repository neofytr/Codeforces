#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1000000) 

bool prime[MAX + 1];

void solve() {
	int d;
	cin >> d;

	int p, q;
	for (int r = d + 1; r <= MAX; r++)
		if (prime[r]) {
			p = r;
			break;
		}

	for (int r = d + p; r <= MAX; r++)
		if (prime[r]) {
			q = r;
			break;
		}

	cout << min(p * p * p, p * q) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	memset((void *)prime, true, MAX);
	for (int r = 2; r <= MAX; r++)
		if (prime[r])
			for (int j = 2 * r; j <= MAX; j += r)
				prime[j] = false;

	while(t--) {
		solve();
	}
}