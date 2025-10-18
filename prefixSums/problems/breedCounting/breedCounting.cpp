#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: breedCounting
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=572
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    freopen("bcount.out", "w", stdout);
    freopen("bcount.in", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> hol(n + 1, 0), guem(n + 1, 0), jer(n + 1, 0);
    for (int r = 1; r <= n; r++) {
        int h = (arr[r - 1] == 1 ? 1 : 0);
        int g = (arr[r - 1] == 2 ? 1 : 0);
        int j = (arr[r - 1] == 3 ? 1 : 0);

        hol[r] += hol[r - 1] + h;
        guem[r] += guem[r - 1] + g;
        jer[r] += jer[r - 1] + j;
    }

    int a, b;
    while(q--) {
        cin >> a >> b;
        a--, b--;
        cout << hol[b + 1] - hol[a] << " ";
        cout << guem[b + 1] - guem[a] << " ";
        cout << jer[b + 1] - jer[a] << endl;
    } 
    return 0;
}