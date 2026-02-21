#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		string s; cin >> s;
		
		vector<char> v(n + 1);
		for (int i = 1; i <= n; i++) 
			v[i] = s[i - 1];
		
		
		int c = 0;
		for (int i = 1; i < n; i++) 
			if (v[i] != v[i + 1]) c++;
		
		if (v[n] != v[1]) c++;
		cout << min(n, c + 1) << endl;
	}
	
	return 0;
}