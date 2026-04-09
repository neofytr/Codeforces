#include <bits/stdc++.h>
using namespace std;

#define int long long 
bitset<(1LL << 32)> b(0);

int32_t main() {
	int q, s, a, x;
	cin >> q >> s >> a >> x;

	int sum = 0;

	// first operation
	if (s & 1) {
		if (!b[s / 2])
			sum += s / 2;
		b[s / 2] = true;
	}
	else {
		if (b[s / 2])
			sum -= s / 2;
		b[s / 2] = false;
	}

	for (int r = 2; r <= q; r++) {
		s = (a * s + x) & ((1LL << 32) - 1);

		if (s & 1) {
			if (!b[s / 2])
				sum += s / 2;
			b[s / 2] = true;
		}
		else {
			if (b[s / 2])
				sum -= s / 2;
			b[s / 2] = false;
		}	
	}
	cout << sum << endl;
	return 0;
}