#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(n);
    for (int &val : a)
        cin >> val;
    for (int &val : b)
        cin >> val;

    multiset<int> ms(a.begin(), a.end());
    int total = 0;

    for (int &eltB : b) {
        int target = m - eltB; // i want to get as close to m as possible so that the mod operation gives the closest possible to zero
        auto itr = ms.lower_bound(target);

        if (itr == ms.end()) {
            // there is nothing in the array that is >= target
            // pick the smallest one (since there is nothing >= target, this will give the smallest value of (a + b) mod m)
            itr = ms.begin();
        }

        int eltA = *itr;
        ms.erase(itr);
        total += (eltA + eltB) % m;
    }

    cout << total << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}