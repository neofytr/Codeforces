#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float double

// Problem: cowHomework
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=762
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    freopen("homework.in", "r", stdin);
    freopen("homework.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] += prefix[r - 1] + arr[r - 1];

    vector<pair<float, int>> marks;
    // mini[r] is the minimum in the range [r, n - 1]
    vector<int> mini(n);
    mini[n - 1] = arr[n - 1];
    for (int r = n - 2; r >= 0; r--)
        mini[r] = min(mini[r + 1], arr[r]);

    for (int k = 1; k <= n - 2; k++) {
        int left = k;
        int right = n - 1;
        float m = (prefix[right + 1] - prefix[left] - mini[left]) / (float)(right - left);
        marks.push_back({m, k});
    }   

    sort(marks.begin(), marks.end(), [](const auto &p1, const auto &p2) {
        return p1.first > p2.first;
    });

    double m = marks[0].first;
    vector<int> kvals;
    for (auto &[mr, k] : marks) {
        if (mr < m)
            break;
        else 
            kvals.push_back(k);
    }

    sort(kvals.begin(), kvals.end());
    for (int k : kvals)
        cout << k << endl;
    return 0;
}