#include <bits/stdc++.h>
using namespace std;

#define int long long 

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        vector<int> mp(2 * 1e5 + 1);
        for (int c : changed)
            mp[c]++;
        
        vector<int> res;
        for (int elt = 0; elt <= 1e5; elt++) {
            int cnt = mp[elt];
            if (!elt && !(cnt & 1)) {
                for (int r = 1; r <= cnt / 2; r++)
                    res.push_back(elt);
                mp[elt] = 0;
            } else if (!elt && (cnt & 1))
                return {};
            else if (cnt >= 1 && mp[2 * elt] >= cnt) {
                for (int r = 1; r <= cnt; r++)
                    res.push_back(elt);
                mp[2 * elt] -= cnt, mp[elt] = 0;
            }
        }

        for (int elt = 0; elt <= 1e5; elt++)
            if (mp[elt] > 0)
                return {};

        return res;
    }
};

int32_t main() {
    int n;
    cin >> n;

    vector<int> c(n);
    for (int &val : c) cin >> val;

    Solution soln;
    vector<int> res = soln.findOriginalArray(c);

    for (int r : res)
        cout << r << " ";
    cout << endl;
    return 0;
}