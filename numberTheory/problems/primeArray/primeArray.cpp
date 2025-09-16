#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: primeArray
// URL: https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/prime-array-5e448ef6/
// Difficulty: easy
// Tags:
// Strategy:

#define MAX 100000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<bool> isPrime(MAX + 1, true);
    for (int r = 2; r <= MAX; r++)
        if (isPrime[r])
            for (int j = 2 * r; j <= MAX; j += r)
                isPrime[j] = false;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int ones = 0;
        int primes = 0;
        for (const int val : arr)
            if (val == 1)
                ones++;
            else if (isPrime[val])
                primes++;

        // choose one prime and two ones
        const int two = (primes >= 1 && ones >= 2) ? primes * (((ones) * (ones - 1)) / 2) : 0;
        cout << two << endl;
    }
    return 0;
}