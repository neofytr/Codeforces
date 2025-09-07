#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> e(n);
        for (int i = 0; i < n; i++) {
            cin >> e[i];
        }

        sort(e.begin(), e.end());

        int count = 0;
        int groups = 0;

        for (int i = 0; i < n; i++) {
            count++;
            if (count >= e[i]) {
                groups++;
                count = 0;
            }
        }
        cout << groups << endl;
    }
    return 0;
}
