#include <bits/stdc++.h>
using namespace std;

void solve() {
    int numProducts, numVouchers;
    cin >> numProducts >> numVouchers;

    vector<long long> prices(numProducts);
    long long totalCost = 0;
    for (int i = 0; i < numProducts; ++i) {
        cin >> prices[i];
        totalCost += prices[i];
    }

    vector<int> vouchers(numVouchers);
    for (int i = 0; i < numVouchers; ++i) {
        cin >> vouchers[i];
    }

    sort(prices.rbegin(), prices.rend());
    sort(vouchers.begin(), vouchers.end());

    long long discount = 0;
    int productIndex = 0;

    for (int i = 0; i < numVouchers; ++i) {
        int groupSize = vouchers[i];
        if (productIndex + groupSize > numProducts)
            break;
        if (groupSize == 1) {
            discount += prices[productIndex];
        } else {
            discount += prices[productIndex + groupSize - 1];
        }
        productIndex += groupSize;
    }

    cout << totalCost - discount << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;
    while (testCases--) {
        solve();
    }

    return 0;
}
