#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int original = n;
    vector<int> factors;

    for (int r = 2; r * r <= n; r++) {
        while (n % r == 0) {
            factors.push_back(r);
            n /= r;
        }
    }
    if (n > 1) factors.push_back(n);

    if ((int)factors.size() < k) {
        cout << -1 << "\n";
        return 0;
    }

    while ((int)factors.size() > k) {
        int last = factors.back();
        factors.pop_back();
        factors.back() *= last;
    }

    for (int f : factors)
        cout << f << " ";
    cout << "\n";

    return 0;
}
