#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> perm(n);
        for (int &val : perm)
            cin >> val;

        multiset<int> sorted(perm.begin(), perm.end());

        int l = 0;
        int r = n - 1;
        bool found = false;
        while (l < r && !found) {
            int maxi = *sorted.rbegin();
            int mini = *sorted.begin();

            if (perm[l] == maxi || perm[l] == mini) {
                sorted.erase(sorted.find(perm[l]));
                l++;
                continue;
            }

            if (perm[r] == maxi || perm[r] == mini) {
                sorted.erase(sorted.find(perm[r]));
                r--;
                continue;
            }

            // both ends are good
            cout << l + 1 << " " << r + 1 << endl; // 1-based
            found = true;
        }

        if (!found)
            cout << -1 << endl;
    }
    return 0;
}
