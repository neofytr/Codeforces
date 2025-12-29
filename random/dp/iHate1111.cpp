#include <bits/stdc++.h>
using namespace std;

#define int long long

unordered_map<int, bool> f;

int cnt(int num) {
    int sum = 0;
    while (num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void solve() {
    int x;
    cin >> x;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}