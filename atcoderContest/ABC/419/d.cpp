#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;
    vector<bool> diff(n + 2, false);

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        diff[l] = !diff[l];
        diff[r + 1] = !diff[r + 1];
    }
    bool is_swapped = false;
    for (int i = 1; i <= n; ++i) {
        is_swapped ^= diff[i];

        if (is_swapped) {
            swap(s[i - 1], t[i - 1]);
        }
    }

    cout << s << endl;
}

int main() {
    solve();
    return 0;
}