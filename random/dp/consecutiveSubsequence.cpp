#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[MAX + 1];
int dp[MAX + 1];
int prv[MAX + 1];

int32_t main() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    set<pair<int, pair<int, int>>> f;
    dp[1] = 1, f.insert({arr[1], {1, 1}});
    prv[1] = -1;
    for (int r = 2; r <= n; r++) {
        auto itr = f.lower_bound({arr[r] - 1, {0, 0}});
        if (itr == f.end() || itr->first != arr[r] - 1) {
            dp[r] = 1, prv[r] = -1;
            continue;
        }

        dp[r] = itr->second.first + 1, prv[r] = itr->second.second;
        itr = f.lower_bound({arr[r], {LLONG_MAX, LLONG_MAX}});
        if (itr == f.end() || itr->first != arr[r]) {
            f.insert({arr[r], {dp[r], r}});
            continue;
        }

        if (dp[r] > itr->second.first)
            f.erase(itr), f.insert({arr[r], {dp[r], r}});
    }

    int maxi = -1;
    for (int r = 1; r <= n; r++)
        maxi = max(dp[r], maxi);
    cout << maxi << endl;
    for (int r = 1; r <= n; r++)
        if (dp[r] == maxi) {
            stack<int> st;
            while (prv[r] != -1)
                st.push(r), r = prv[r];

            st.push(r);
            while (!st.empty())
                cout << st.top() << " ", st.pop();
            cout << endl;
            break;
        }
    return 0;
}