#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	unordered_map<string, string> mp;
	unordered_map<string, int> nm;

	while(n--) {
		string str;
		cin >> str;

		if (mp[str].empty()) {
			mp[str] = str;
			cout << "OK\n";
		} else {
			if (!nm[str])
				nm[str] = 1;
			cout << mp[str] + to_string(nm[str]++) << "\n";
		}
	}
	return 0;
}