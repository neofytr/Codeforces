#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 32768

int dp[MOD + 1];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < MOD; i++)
        dp[i] = LLONG_MAX;
    dp[0] = 0;

    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int x = que.front();
        que.pop();

        if (int one = (x - 1 + MOD) % MOD; dp[one] > dp[x] + 1)
            dp[one] = dp[x] + 1, que.push(one);
        if (!(x % 2)) {
            int two1 = x / 2;
            int two2 = x / 2 + MOD / 2;

            if (dp[two1] > dp[x] + 1)
                dp[two1] = dp[x] + 1, que.push(two1);
            if (dp[two2] > dp[x] + 1)
                dp[two2] = dp[x] + 1, que.push(two2);
        }
    }

    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        cout << dp[x] << " ";
    }
    cout << endl;
}
