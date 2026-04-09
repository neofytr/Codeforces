#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string str;
        cin >> str;

        vector<int> arr(n + 1, 0);
        for (int r = 0; r < n; r++)
            if (str[r] == '0')
                arr[r + 1] = 2;

        int cost = 0;
        for (int r = 1; r <= n; r++) {
            if (!arr[r])
                continue;

            for (int i = r; i <= n; i += r)
                if (arr[i] == 2)
                    cost += r, arr[i] = 1;
                else if (arr[i] == 1)
                    continue;
                else if (!arr[i])
                    break;
        }
        cout << cost << endl;
    }
    return 0;
}