#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;

    for (int i = 2; i * i <= n; i++)
        if (prime[i])
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;

    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (prime[i]) primes.push_back(i);

    int cnt = 0;
    for (int i = 0; i + 1 < primes.size(); i++) {
        int r = primes[i] + primes[i + 1] + 1;
        if (r <= n && prime[r]) cnt++;
    }

    cout << (cnt >= k ? "YES" : "NO") << "\n";
}
