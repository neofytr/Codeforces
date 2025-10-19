#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int val;
        map<int, int> mp;
        for (int r = 1; r <= n; r++)
            cin >> val, mp[val]++;

        int res = 0;
        int prevCount = -1;
        int prevSize = -1;
        for (auto &[sz, cnt] : mp) {
            if (prevSize == -1 || sz > prevSize + 1) // a new set must start from here
                res += cnt;
            else if (cnt > prevCount) // the current set can't handle all the elements, some need to start new
                res += cnt - prevCount;
            prevSize = sz;
            prevCount = cnt;
        }

        cout << res << endl;
    }
    return 0;
}