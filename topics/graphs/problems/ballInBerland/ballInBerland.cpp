#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

void solve() {
    int a, b, k;
    cin >> a >> b >> k;

    // since we have k pairs
    // we select two out of them
    // but in doing so, we have overcounted exactly the following
    // 1. pairs where the boys are the same
    // 2. pairs where the girls are the same
    // these two are mutually exclusive sets since both boys and both girls cannot be the same
    // in two different pairs

    // pairs where the boys are the same
    // for each boy b
    // the number of pairs of pairs formed where both have the boy b is deg(b) * (deg(b) - 1) / 2
    // since all of these are mutually exclusive, we can sum over them

    // pairs where the girls are the same
    // for each girl g
    // the number of pairs of pairs formed where both have the boy b is deg(b) * (deg(b) - 1) / 2
    // since all of these are mutually exclusive, we can sum over them

    vector<int> boys(a);  // boys[r] is the number of pairs boy r is involved in
    vector<int> girls(b); // girls[r] is the number of pairs girl r is involved in

    vector<int> p1(k);
    vector<int> p2(k);
    for (int index = 0; index < k; index++) {
        cin >> p1[index];
        p1[index]--;
    }
    for (int index = 0; index < k; index++) {
        cin >> p2[index];
        p2[index]--;
    }

    for (int index = 0; index < k; index++) {
        boys[p1[index]]++;
        girls[p2[index]]++;
    }

    // total number of possible pairs of the k pairs
    int total = k * (k - 1) / 2;

    // subtract from it the number of pairs where the boys are the same
    for (int by = 0; by < a; by++) {
        total -= (boys[by] * (boys[by] - 1)) / 2;
    }

    // subtract from it the number of pairs where the girls are the same
    for (int g = 0; g < b; g++) {
        total -= (girls[g] * (girls[g] - 1)) / 2;
    }

    cout << total << endl;
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
