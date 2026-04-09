#include <bits/stdc++.h>
using namespace std;

#define int long long
int R[10 + 2];
int L[10 + 2];

void solve() {
    int l, r;
    cin >> l >> r;

    int i = 1;
    while (r)
        R[i++] = r % 10, r /= 10;
    i = 1;
    while (l)
        L[i++] = i % 10, l /= 10;


}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}