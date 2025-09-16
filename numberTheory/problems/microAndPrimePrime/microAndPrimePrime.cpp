#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: microAndPrimePrime
// URL: https://www.hackerearth.com/practice/math/number-theory/primality-tests/practice-problems/algorithm/micro-and-prime-prime-1/
// Difficulty: medium
// Tags:
// Strategy:

#define MAX (1000000)
// prefix[r] is the number of prime numbers in the range [1, r]
array<int, MAX + 1> prefix{};
// pp[r] is the number of primePrime numbers in the range [1, r]
array<int, MAX + 1> pp{};
bitset<MAX + 1> prime;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    // a number r >= 1 is primePrime if the number of prime numbers in the range [1, r] is a prime
    prime.set();
    prime[0] = prime[1] = false;
    for (int r = 2; r * r <= MAX; r++)
        if (prime[r])
            for (int j = r * r; j <= MAX; j += r)
                prime[j] = false;

    prefix[0] = prefix[1] = 0;
    for (int r = 2; r <= MAX; r++)
        prefix[r] = prefix[r - 1] + prime[r];

    pp[0] = pp[1] = 0;
    for (int r = 2; r <= MAX; r++)
        pp[r] = pp[r - 1] + prime[prefix[r]];
    while (t--) {
        int l, r;
        cin >> l >> r;
        cout << pp[r] - pp[l - 1] << endl;
    }
    return 0;
}