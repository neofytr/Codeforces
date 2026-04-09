#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: interestingDrink
// URL: https://codeforces.com/problemset/problem/706/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> price(n);
    for (int &val : price)
        cin >> val;

    sort(price.begin(), price.end());

    int q;
    cin >> q;

    while (q--) {
        int m;
        cin >> m;

        int left = -1;
        int right = n;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (price[mid] > m)
                right = mid;
            else
                left = mid;
        }

        cout << left + 1 << endl;
    }
    return 0;
}