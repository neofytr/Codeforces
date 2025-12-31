#include <bits/stdc++.h>
using namespace std;


// this is a wrong solution fix it lmao it isnt that hard a question
#define int long long

int32_t main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<bool> allowed(26, false);
    for (int i = 0; i < k; i++) {
        char c;
        cin >> c;
        allowed[c - 'a'] = true;
    }

    vector<int> dp(n, 0);

    if (allowed[s[0] - 'a'])
        dp[0] = 1;

    for (int i = 1; i < n; i++) {
        if (allowed[s[i] - 'a'])
            dp[i] = dp[i - 1] + 1;
        else
            dp[i] = 0;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++)
        cnt += dp[i];

    cout << cnt << endl;
}
