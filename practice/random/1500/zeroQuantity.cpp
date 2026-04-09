#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	map<pair<int,int>, int> f;
	int c = 0;
	
	for (int r = 1; r <= n; r++) {
	    if (!a[r] && !b[r]) {
	        c++;
	    }
	    else if (!a[r]) {
	        continue;
	    }
	    else {
	        int A = a[r], B = b[r];
	        int g = gcd(abs(A), abs(B));
	        A /= g;
	        B /= g;
	
	        if (A < 0) {
	            A = -A;
	            B = -B;
	        }
	
	        f[{-B, A}]++;
	    }
	}
	
	int maxi = 0;
	for (auto &[_, cnt] : f)
	    maxi = max(maxi, cnt);
	
	int ans = maxi + c;
	cout << ans << endl;
	return 0;
}