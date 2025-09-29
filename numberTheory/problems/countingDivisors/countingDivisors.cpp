#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: countingDivisors
// URL: https://cses.fi/problemset/task/1713
// Difficulty: medium
// Tags: 
// Strategy: 

#define MAX 1000000

vector<int> primeFactorization(int x) {
    vector<int> res;
    if (x <= 1)
        return res;

    for (int r = 2; r * r <= x; r++)
        while(!(x % r))
            res.push_back(r), x /= r;
    if (x > 1) res.push_back(x);
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    // prime[r] is the smallest divisor (prime) of r, for r >= 2
    vector<int> prime(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        for (int j = r; j <= MAX; j += r)
            if (prime[j] == -1)
                prime[j] = r;

    while(n--) {
        int x;
        cin >> x;

        // We are to find the number of divisors of x
        // We can easily find the number of divisors of x if we know the prime factorization of x
        // We can prime factorize x in log(x) if we do some precomputation

        int cnt = 1;
        while(x != 1) {
            int p = prime[x];
            int num = 1;
            while(!(x % p))
                num++, x /= p;
            cnt *= num;
        }
        cout << cnt << "\n";
    }
    return 0;
}