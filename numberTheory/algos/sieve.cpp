#include <bits/stdc++.h>
using namespace std;

#define int long long

// returns all the prime numbers in the range [1, n]
vector<int> sieve(const int n) {
    vector<int> ans;
    if (n <= 1)
        return ans;

    vector<int> vis(n + 1, false);
    for (int r = 2; r <= n; r++)
        if (!vis[r]) {
            ans.push_back(r);
            for (int j = r * r; j <= n; j += r) // we can just start from r * r because any x < r * r will have
                                                // a prime factor t that is < r, and thus would've been marked in the iteration r = t
                vis[j] = true;
        }
    return ans;
}
