#include <bits/stdc++.h>
using namespace std;

#define int long long 

// lets say we finish off the monsters after the kth shot

// for it to be an enhanced shot, 7 | k
// Let k = 7 * s

// damage dealt = s + s + s + 6 * s = 9 * s = a + b + c
// however, the monsters must atleast survive the enhanced shots individually, so
// a >= s, b >= s, c >= s

void solve() {
	int a, b, c;
	cin >> a >> b >> c;

	if ((a + b + c) % 9){
		cout << "NO\n";
		return;
	}

	int s = (a + b + c) / 9;
	if (a >= s && b >= s && c >= s) 
		cout << "YES\n";
	else 
		cout << "NO\n"
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}