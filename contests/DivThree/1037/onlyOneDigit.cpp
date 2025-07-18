// http://codeforces.com/contest/2126/problem/A

#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x;
    cin >> x;

    int minDig = -1;
    int dig;
    while (x) {
        dig = x % 10;
        minDig = min(minDig, dig);
        x /= 10;
    }

    cout << dig << endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}