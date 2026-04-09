#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int p, q, x, y;
	cin >> p >> q >> x >> y;

	if (x >= p && x <= p + 99 && y >= q && y <= q + 99)
		cout << "Yes";
	else 
		cout << "No";
	cout << endl;
	return 0;
}