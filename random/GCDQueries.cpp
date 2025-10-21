#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 1000000

int smallestPrime[MAX + 1];

void buildSPF() {
    for (int i = 0; i <= MAX; i++)
        smallestPrime[i] = -1;

    for (int r = 2; r <= MAX; r++)
        if (smallestPrime[r] == -1)
            for (int j = r; j <= MAX; j += r)
                if (smallestPrime[j] == -1)
                    smallestPrime[j] = r;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildSPF();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        multiset<int> ms;
        unordered_map<int, multiset<int>> mp;

        for (int &val : arr) {
            cin >> val;
            ms.insert(val);

            int num = val;
            while (num != 1) {
                int p = smallestPrime[num];
                while (num % p == 0)
                    num /= p;
                mp[p].insert(val);
            }
        }

        int q;
        cin >> q;
        while (q--) {
            int x;
            cin >> x;

            int miniVal = LLONG_MAX;
            int tmp = x;

            while (tmp != 1) {
                int p = smallestPrime[tmp];
                while (tmp % p == 0)
                    tmp /= p;

                if (!mp[p].empty())
                    miniVal = min(miniVal, *mp[p].begin());
            }

            if (miniVal == LLONG_MAX)
                miniVal = *ms.begin();

            cout << miniVal << " ";

            ms.erase(ms.find(miniVal));

            int num = miniVal;
            while (num != 1) {
                int p = smallestPrime[num];
                while (num % p == 0)
                    num /= p;
                mp[p].erase(mp[p].find(miniVal));
            }
        }
        cout << endl;
    }
    return 0;
}
