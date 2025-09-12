#include <bits/stdc++.h>
using namespace std;

#define int long long

// runs in O(log(b))
// we always maintain a >= b
int gcd(const int a, const int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}