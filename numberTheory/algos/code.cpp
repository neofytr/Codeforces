#include <bits/stdc++.h>
using namespace std;

#define int long long

// runs in O(log(b))
// we always maintain a >= b
int gcd(const int a, const int b) {
    if (a < 0 || b < 0)
        return -1;
    if (!b)
        return a;
    return gcd(b, a % b);
}

vector<int> div(const int b) {
    vector<int> ans;
    if (b <= 0)
        return ans;

    for (int r = 1; r * r <= b; r++) {
        if (!(b % r)) {
            ans.push_back(r);
            if (r != b / r)
                ans.push_back(b / r);
        }
    }
    return ans;
}

// function to find all primes <= n using the Sieve of Eratosthenes
vector<int> primes(const int n) {
    vector<int> ans;
    if (n <= 1)
        return ans;
    vector<bool> vis(n + 1, true);
    for (int r = 2; r <= n; r++) {
        if (vis[r]) {
            ans.push_back(r);
            for (int x = r * 2; x <= n; x += r)
                vis[x] = false;
        }
    }
    // Proposition -> If at the start of iteration r = x, vis[x] = true, then x is a prime; otherwise, it is not
    // Proof -> We prove via induction on x
    // Base Case (x = 2)
    // At the start of iteration x = 2, vis[2] = true since it's the first iteration of the loop.
    // The base case thus holds
    // Inductive Step
    // Assume the proposition is true for all 2 <= w <= x for some x >= 2
    // Assume that at the start of iteration r = x + 1, vis[x + 1] = true
    // Since the proposition is true for all 2 <= w <= x, the if statement would've run for all 2 <= w <= x that are primes
    // This would have resulted in the marking of all multiples w of p that are <= n for all 2 <= p <= x that are primes to value false
    // So, if vis[x + 1] is true, this means that it has not been marked false, and thus, it is not a multiple of any prime <= x
    // Thus, x + 1 is a prime itself
    // Otherwise, if it would've been marked false at the beginning of iteration r = x + 1, it must be a multiple of
    // some prime <= x, and thus not a prime itself
    // Thus the proposition is true for r = x + 1
    // The induction step thus holds
    return ans;
}