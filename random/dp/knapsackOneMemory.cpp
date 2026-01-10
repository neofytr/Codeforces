#include <bits/stdc++.h>
using namespace std;

#define int long long
#define WMAX (int)(1e5)
#define NMAX (int)(1e2)

int front[WMAX + 1], back[WMAX + 1];
int wt[NMAX + 1], val[NMAX + 1];

int32_t main() {
    int n, W;
    cin >> n >> W;

    for (int r = 1; r <= n; r++)
        cin >> wt[r] >> val[r];

    for (int r = 1; r <= n; r++) {
        for (int w = 0; w <= W; w++) {
            back[w] = front[w];
            if (w >= wt[r])
                back[w] = max(back[w], front[w - wt[r]] + val[r]);
        }
        swap(front, back);
    }

    int maxi = LLONG_MIN;
    for (int w = 0; w <= W; w++)
        maxi = max(maxi, front[w]);
    cout << maxi << endl;
    return 0;
}