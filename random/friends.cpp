#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> has(n), spends(n);
        for (int &val : spends)
            cin >> val;
        for (int &val : has)
            cin >> val;

        vector<int> c(n);
        for (int r = 0; r < n; r++)
            c[r] = has[r] - spends[r];

        sort(c.begin(), c.end());
        int l = 0, r = n - 1, cnt = 0;
        while (l < r) {
            if (c[l] < 0 && c[l] + c[r] >= 0)
                cnt++, l++, r--;
            else if (c[l] < 0 && c[l] + c[r] < 0)
                l++;
            else if (c[l] >= 0)
                l++, r--, cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}

// -1 0 3