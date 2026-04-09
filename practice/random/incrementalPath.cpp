#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(1e9)

bitset<MAX + 1> col;

void solve() {
	int n, m;
	cin >> n >> m;

	string str;
	cin >> str;

	col.set();
	set<int> black;
	vector<int> arr(m + 1);
	for (int r = 1; r <= m; r++) cin >> arr[r], black.insert(arr[r]), col[arr[r]] = false;

	int last = 1;
	for (int r = 1; r <= n; r++)
		if (str[r - 1] == 'A')
			last++, black.insert(last), col[last] = 0;
		else 
			last = col._Find_next(last), black.insert(last), col[last] = 0;
	
	cout << black.size() << endl;
	for (int b : black)
		cout << b << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}