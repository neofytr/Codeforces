#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: evenOddGame
// URL: https://codeforces.com/problemset/problem/1472/D
// Difficulty: medium
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        // sort descending
        sort(a.rbegin(), a.rend());

        int alice = 0, bob = 0;
        for (int i = 0; i < n; i++) {
            if (!(i & 1)) { // Alice's turn
                if (!(a[i] & 1))
                    alice += a[i];
            } else { // Bob's turn
                if (a[i] & 1)
                    bob += a[i];
            }
        }

        if (alice > bob)
            cout << "Alice\n";
        else if (bob > alice)
            cout << "Bob\n";
        else
            cout << "Tie\n";
    }
    return 0;
}
