#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    int maxi = LLONG_MIN;
    int val;
    for (int r = 1; r <= n; r++)
        cin >> val, maxi = max(maxi, val);
    cout << maxi << endl;
    return 0;
}