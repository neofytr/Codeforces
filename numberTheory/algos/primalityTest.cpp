#include <bits/stdc++.h>
using namespace std;

#define int long long

// O(sqrt(n))
bool isPrime(const int n) {
    if (n <= 1)
        return false;

    for (int r = 2; r * r <= n; r++)
        if (!(n % r))
            return false;
    return true;
}

int32_t main() {
    int n;
    cin >> n;

    cout << isPrime(n) ? "yes\n" : "no\n" << endl;
    return 0;
}