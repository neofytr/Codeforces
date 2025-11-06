#include <bits/stdc++.h>
using namespace std;

#define MAX (int)(1e6)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> freq(MAX + 1, 0);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        freq[x]++;
    }

    // f[d] = count of numbers divisible by d
    vector<long long> f(MAX + 1, 0);
    for (int d = 1; d <= MAX; ++d) {
        for (int multiple = d; multiple <= MAX; multiple += d)
            f[d] += freq[multiple];
    }

    // g[d] = number of pairs with gcd exactly d
    vector<long long> g(MAX + 1, 0);
    for (int d = MAX; d >= 1; --d) {
        if (f[d] < 2) continue; // no pairs possible
        long long pairs = f[d] * (f[d] - 1) / 2;
        for (int multiple = 2 * d; multiple <= MAX; multiple += d)
            pairs -= g[multiple];
        g[d] = pairs;
    }

    cout << g[1] << "\n";
    return 0;
}
