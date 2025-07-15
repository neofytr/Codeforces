#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    const long long total = accumulate(arr.begin(), arr.end(), 0ll);
    const int k = n / 2; // subset size
    vector<vector<bool> > dp(k + 1, vector<bool>(total + 1, false));
    dp[0][0] = true;

    for (const long long num: arr) {
        // iterate in reverse to avoid reuse
        for (int i = k; i >= 1; i--) {
            for (long long s = total; s >= num; s--) {
                if (dp[i - 1][s - num]) {
                    dp[i][s] = true;
                }
            }
        }
    }

    long long result = LONG_LONG_MAX;
    for (int s = 0; s <= total; ++s) {
        if (dp[k][s]) {
            const long long other = total - s;
            result = min(result, abs(s - other));
        }
    }

    cout << result << endl;
    return EXIT_SUCCESS;
}
