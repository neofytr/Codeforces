#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int cnt = 0;
	string str;

	while (cin >> str) {
		int maxi = LLONG_MIN;
		for (int tens = 0; tens < str.length() - 1; tens++)
			for (int ones = tens + 1; ones < str.length(); ones++) 
				maxi = max(maxi, (int)(str[ones] - '0') + 10 * (str[tens] - '0'));
		cnt += maxi;
	}
	cout << cnt << endl;
	return 0;
}