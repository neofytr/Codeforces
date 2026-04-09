#include <bits/stdc++.h>
using namespace std;

#define int long long

// a >= 0 and p is a prime
// We want to calculate the MMI of a modulo p
// Using fermat's theorem, it would simply be a^(p - 2) % p
int inv_prime(const int a, const int p) {
    int pw = p - 2;
    int base = a % p;
    if (!base) // gcd(a, p) != 1
        return -1;

    int res = 1;
    while (pw) {
        if (pw & 1)
            res = res * base % p;
        base = base * base % p;
        pw >>= 1;
    }
    return res;
}

int x, y;
int extendedEuclid(const int a, const int b) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    const int g = extendedEuclid(b, a % b);
    const int x1 = x, y1 = y;
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// a >= 0 and p > 0
// Calculate MMI of a modulo p
int inv(const int a, const int p) {
    if (extendedEuclid(a, p) != 1)
        return -1;          // MMI doesn't exist
    return (x % p + p) % p; // ensuring a positive result is returned
}