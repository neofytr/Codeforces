#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	if (n & 1) 
		cout << 0 << endl;
	else 
		cout << (1ll << (n >> 1)) << endl;
	return 0;
}	