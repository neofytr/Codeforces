#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        if (n == 0) {
            cout << 0 << '\n';
            continue;
        }
        long long sum_delta = 0;
        int max_delta = 0;
        int adjusted_prev = a[0];
        for (int i = 1; i < n; ++i) {
            int required = max(a[i], adjusted_prev);
            int delta_i = required - a[i];
            sum_delta += delta_i;
            if (delta_i > max_delta) {
                max_delta = delta_i;
            }
            adjusted_prev = required;
        }
        cout << sum_delta + max_delta << '\n';
    }
    return 0;
}