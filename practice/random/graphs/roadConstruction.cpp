#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> forbidden_count(n + 1, 0);
    vector<vector<bool>> bad(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        bad[a][b] = bad[b][a] = true;
        forbidden_count[a]++;
        forbidden_count[b]++;
    }

    int center = -1;
    for (int i = 1; i <= n; i++) {
        if (forbidden_count[i] == 0) {
            center = i;
            break;
        }
    }

    // guaranteed to exist by problem statement
    cout << n - 1 << "\n";
    for (int i = 1; i <= n; i++) {
        if (i != center) {
            cout << center << " " << i << "\n";
        }
    }

    return 0;
}
