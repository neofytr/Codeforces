#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    int cnt = 0;
  	sort(arr.begin(), arr.end());
    for (int j = 2; j <= n; j++) {
    	int l1 = l - arr[j], l2 = r - arr[j];

    	auto itr1 = upper_bound(arr.begin() + 1, arr.begin() + j, l2) - 1;
    	auto itr2 = lower_bound(arr.begin() + 1, arr.begin() + j, l1);

    	cnt += (itr1 - itr2 + 1);
    }
    cout << cnt << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
