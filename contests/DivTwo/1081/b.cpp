#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		string s; cin >> s;
		
		vector<int> o, z;
		for(int i=0; i<n; ++i) 
			if(s[i] == '1') o.pb(i+1);
			else z.pb(i+1);
	
		if(!(sz(o) % 2)) {
			cout << sz(o) << endl;
			for(auto x : o) cout << x << endl;
			cout << endl;
		} else if(!(n % 2)) {
			cout << sz(z) << endl;
			for(auto x : z) cout << x << endl;
			cout << endl;
		} else 
			cout << -1 << endl;
	}
	return 0;
}