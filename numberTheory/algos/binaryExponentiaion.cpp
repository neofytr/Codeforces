#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)

// modular exponentiation
int pwm(const int a, const int b) {
    if (!b)
        return 1;
    const int r = pwm(a, b / 2);
    if (b & 1)
        return r * r % MOD * a % MOD;
    return r * r % MOD;
}

// binary exponentiation
int pw(const int a, const int b) {
    if (!b)
        return 1;
    const int r = pw(a, b / 2);
    if (b & 1)
        return r * r * a;
    return r * r;
}