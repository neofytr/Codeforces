#include <bits/stdc++.h>
using namespace std;

#define int long long
#define C(n) ((((n) * ((n)- 1))) / 2)

int32_t main() {
    int k, s;
    cin >> k >> s;

    cout << C(s + 2) - 3 * C(max(0LL, s + 2 - (k + 1))) + 3 * C(max(0LL, s + 2 - 2 * (k + 1))) - C(max(0LL, s + 2 - 3 * (k + 1))) << endl;
    return 0;
}