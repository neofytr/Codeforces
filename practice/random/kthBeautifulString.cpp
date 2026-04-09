// https://codeforces.com/problemset/problem/1328/B

#include <bits/stdc++.h>
using namespace std;

#define int long long
int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        int tot = 0;
        string str;
        bool done = false;
        for (int firstB = n - 2; firstB >= 0 && !done; firstB--) {
            int count = (n - firstB - 1);
            tot += count;
            if (tot >= k) {
                tot -= count;
                int i = n - k + tot;
                for (int j = 0; j < n; j++) {
                    if (j == firstB || j == i)
                        str.push_back('b');
                    else
                        str.push_back('a');
                }
                cout << str << endl;
                done = true;
            }
        }
    }
    return EXIT_SUCCESS;
}