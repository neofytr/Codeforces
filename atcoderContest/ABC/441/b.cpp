#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	string s, t;
	cin >> s >> t;

	unordered_map<char, bool> tak, aoki;
	for (char c : s) tak[c] = true;
	for (char c : t) aoki[c] = true;

	int q;
	cin >> q;

	string w;
	while (q--) {
		cin >> w;
		bool both = true, taki = true, aki = true;
		for (char c : w) {
			if (!aoki[c] || !tak[c])
				both = false;
			if (!aoki[c]) aki = false;
			if (!tak[c]) taki = false;
		}

		if (both)
			cout << "Unknown\n";
		else if (taki)
			cout << "Takahashi\n";
		else if (aki)
			cout << "Aoki\n";
		else 
			cout << "Unknown\n";
	}
	return 0;
}