#include <bits/stdc++.h>
using namespace std;

#define int long long 
void solve() {
	int n, k;
	cin >> n >> k;

	string str;
	cin >> str;

	vector<int> f(26);
	for (char c : str)
		f[c - 'a']++;

	auto can = [&](int x) -> bool {
		// can the shortest of the k strings be of length atleast x?
		// or equivalently, can the k strings be of length atleast x each?
    	if (!(x & 1)) {
    		int pairCnt = 0;
    		int pairsRequired = (x / 2) * k;
    		for (int c : f)
    			pairCnt += (c / 2);

    		return pairCnt >= pairsRequired;
    	} else {
    		int pairCnt = 0;
    		int singleCnt = 0;
    		int pairsRequired = (x / 2) * k;
    		int singlesRequired = k;

    		for (int c : f)
    			pairCnt += (c / 2), singleCnt += (c % 2);
    		singleCnt += max(0ll, (pairCnt - pairsRequired) * 2);
    		return pairCnt >= pairsRequired && singleCnt >= singlesRequired;
    	}
	
    	return true;
	};	


	int left = 1; // the shortest of the k strings is of atleast length 1
	int right = n / k + 1; // not possible

	while(right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid)) 
			left = mid;
		else 
			right = mid;
	}

	cout << left << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}