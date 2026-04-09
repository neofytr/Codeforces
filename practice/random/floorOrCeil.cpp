#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int x, n, m;
	cin >> x >> n >> m;
	int y = x;

	// Let x in binary be
	// x = (l)(r)
	// where r = the last (n + m) bits of x
	// and l = the remaining higher bits

	// When we perform (n + m) total operations, we shift out
	// exactly (n + m) lower order bits of x
	// The final result becomes l or l + 1 (if a carry escapes r)

	// A carry can escape r iff there is a set bit in the higher order
	// m bits of r and we can achieve l + 1 if we do all type 1 operations first, and then type 2 operations
	// So, the maximum value of x at the end will be (l + 1) if there is a set bit in
	// the higher order m bits of r; otherwise, it will be l
	// So, to get the maximum possible value, we do all the type 1 operations first 
	// and then type 2

	int maxi;
	for (int typeone = 1; typeone <= n; typeone++){
		x >>= 1;
		if (!x)
			break;
	}
	for (int typetwo = 1; typetwo <= m; typetwo++) {
		x = (x >> 1) + (x & 1);
		if (x <= 1)
			break;
	}

	// 0 <= x <= 1e9
	// So, x at max has 30 bits since 2^30 ~ 1e9
	
	// After n + m operations, we would get atleast l
	// To guarantee that we can make l, we should put a type 1
	// operation at last so that even if there is a carry, it absorbs it
	// If n == 0 and there is a set bit, the minimum is also l + 1
	// If n > 0, the minimum is always l
	// So, to make the minimum value, we do all ceilings first and then floors
	for (int typetwo = 1; typetwo <= m; typetwo++) {
		y = (y >> 1) + (y & 1);
		if (y <= 1)
			break;
	}
	for (int typeone = 1; typeone <= n; typeone++) {
		y >>= 1;
		if (!y)
			break;
	}

	cout << y << " " << x << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}