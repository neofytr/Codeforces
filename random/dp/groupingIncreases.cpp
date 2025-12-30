#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[MAX + 1];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}