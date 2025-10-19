#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (2*100000)

bitset<MAX + 1> bt;

int32_t main() {
    int n, q;
    cin >> n >> q;

    int sum = 0;
    int y = 0;
    int scndIdx = 0;
    vector<int> firstIdx(n + 1, 0);

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r], sum += arr[r];

    int t, i, x;
    for (int r = 1; r <= q; r++) {
        cin >> t;
        if (t == 1) {
            cin >> i >> x;
            if (firstIdx[i] >= scndIdx)
                sum -= arr[i];
            else
                sum -= y;
            firstIdx[i] = r;
            arr[i] = x;
            sum += x;
        } else {
            cin >> x;
            scndIdx = r;
            y = x;
            sum = n * x;
        }
        cout << sum << endl;
    }
    return 0;
}