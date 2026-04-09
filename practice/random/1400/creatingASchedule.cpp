#include <bits/stdc++.h>
using namespace std;

#define int long long

int score(const vector<pair<int,int>>& one,
          const vector<pair<int,int>>& two,
          int n) {
    int s = 0;
    for (int i = 1; i <= n; i++)
        s += llabs(one[i].first - two[i].first);
    return s;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<pair<int,int>> a(m + 1);

    for (int i = 1; i <= m; i++) {
        int v; cin >> v;
        int x = v;
        vector<int> dig(11, -1);
        int d = 1;

        while (v) {
            dig[d++] = v % 10;
            v /= 10;
        }

        for (int j = 10; j >= 1; j--) {
            if (dig[j] == -1) continue;
            if (j >= 4)
                a[i] = {dig[j] * 10 + dig[j - 1], x};
            else
                a[i] = {dig[j], x};
            break;
        }
    }

    sort(a.begin() + 1, a.end());
    if (n == 1) {
    for (int t = 1; t <= 3; t++)
        cout << a[1].second << " " << a[m].second << " ";
    cout << "\n";
    return;
}
    vector<pair<int,int>> b(1);
    int L = 1, R = m;
    while ((int)b.size() <= n) {
        if ((int)b.size() <= n) b.push_back(a[L++]);
        if ((int)b.size() <= n) b.push_back(a[R--]);
    }

    vector<pair<int,int>> oneA(n + 1), twoA(n + 1);
    vector<pair<int,int>> oneB(n + 1), twoB(n + 1);

    int k = n / 2;

    for (int i = 1; i <= k; i++) {
        oneA[i] = oneB[i] = b[i];
        oneA[k + i + (n & 1)] = oneB[k + i + (n & 1)] = b[n - i + 1];

        twoA[i] = twoB[i] = b[n - i + 1];
        twoA[k + i + (n & 1)] = twoB[k + i + (n & 1)] = b[i];
    }

    if (n & 1) {
        oneA[k + 1] = b[k + 1];
        twoA[k + 1] = b[n - k];

        oneB[k + 1] = b[n - k];
        twoB[k + 1] = b[k + 1];
    }

    auto &one = (score(oneA, twoA, n) > score(oneB, twoB, n)) ? oneA : oneB;
    auto &two = (score(oneA, twoA, n) > score(oneB, twoB, n)) ? twoA : twoB;

    for (int i = 1; i <= n; i++) {
        for (int t = 1; t <= 3; t++)
            cout << one[i].second << " " << two[i].second << " ";
        cout << "\n";
    }
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
