#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (100)

int32_t main() {
	int val = 50;
	string str;
	int cnt = 0;
	while (cin >> str) {
		int d = stoi(str.substr(1)) % MOD;
		if (str[0] == 'L')
			val = (val - d + MOD) % MOD;
		else 
			val = (val + d) % MOD;
		if (!val)
			cnt++;
		cout << str << " " << val << endl;
	}
	cout << cnt << endl;
	return 0;
}