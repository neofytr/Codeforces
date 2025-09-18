#include <bits/stdc++.h>
using namespace std;

void solve() {
    int numProducts, numVouchers;
    cin >> numProducts >> numVouchers;

    vector<long long> prices(numProducts);
    long long tc = 0;
    for (int i = 0; i < numProducts; ++i) {
        cin >> prices[i];
        tc += prices[i];
    }

    vector<int> vouchers(numVouchers);
    for (int i = 0; i < numVouchers; ++i) {
        cin >> vouchers[i];
    }

    sort(prices.rbegin(), prices.rend());
    sort(vouchers.begin(), vouchers.end());

    long long discount = 0;
    int pi = 0;

    for (int i = 0; i < numVouchers; ++i) {
        int size = vouchers[i];
        if (pi + size > numProducts)
            break;
        if (size == 1) {
            discount += prices[pi];
        } else {
            discount += prices[pi + size - 1];
        }
        pi += size;
    }

    cout << tc - discount << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
