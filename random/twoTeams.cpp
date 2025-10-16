#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int maxFreq = LLONG_MIN;
	int val;
	unordered_map<int, int> freq;
	for (int r = 1; r <= n; r++)
		cin >> val, freq[val]++, maxFreq = max(maxFreq, freq[val]);

	int distinctCount = freq.size();

	if (maxFreq - 1 >= distinctCount) {
		cout << distinctCount << endl;
	} else if (distinctCount - 1 >= maxFreq) {
		cout << maxFreq << endl;
	} else {
		cout << maxFreq - 1 << endl;
	}
}

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
}