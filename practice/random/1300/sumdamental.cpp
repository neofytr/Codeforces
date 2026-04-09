#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, x;
    cin >> n >> x;

    if ((n & 1) && (x & 1))
        cout << n + x - 1 << endl;
    else if (!(n & 1) && !(x & 1))
        cout << n + x - 1 << endl;
    else if ((n & 1) && !(x & 1))

}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}