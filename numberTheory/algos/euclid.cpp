#include <bits/stdc++.h>
using namespace std;

#define int long long

// assumed that initially -> a >= b >= 0
int gcd(const int a, const int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}