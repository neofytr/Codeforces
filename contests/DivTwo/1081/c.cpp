#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>

void slv() {
	int n, h, k, s = 0; cin >> n >> h >> k;
	
	vi a(n), p(n), mn(n), mx(n);
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		s += a[i];
		p[i] = a[i] + (i ? p[i-1] : 0);
		mn[i] = i ? min(mn[i-1], a[i]) : a[i];
	}
	
	mx[n-1] = a[n-1];
	for(int i=n-2; i>=0; --i) mx[i] = max(mx[i+1], a[i]);
	
	int c = (h - 1) / s;
	int rm = h - c * s;
	int res = n;
	
	for(int i=0; i<n; ++i) {
		int g = (i + 1 < n) ? max(0LL, mx[i+1] - mn[i]) : 0;
		if(p[i] + g >= rm) {
			res = i + 1;
			break;
		}
	}
	cout << c * (n + k) + res << endl;
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while(t--) slv();
	return 0;
}