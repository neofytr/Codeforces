#include <bits/stdc++.h>
using namespace std;

#define int long long

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    for (int p : primes) 
        for (int x : arr) 
            if (x % p != 0) { 
                cout << p << endl;
                return;
            }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
