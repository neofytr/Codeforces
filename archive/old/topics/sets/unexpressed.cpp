#include <bits/stdc++.h>
using namespace std;

long long calculate(long long base, long long exponent, unordered_map<long long, long long> &memoization) {
    if (exponent == 0) return 1;
    if (exponent == 1) return base;

    if (memoization.count(exponent)) return memoization[exponent];

    long long half = calculate(base, exponent / 2, memoization);
    long long result = half * half;

    if (exponent % 2 == 1) {
        result *= base;
    }

    memoization[exponent] = result;
    return result;
}


int main() {
    long long n;
    cin >> n;
    unordered_set<long long> arr;

    for (long long base = 2; base <= static_cast<long long>(sqrt(n)); base++) {
        unordered_map<long long, long long> memo;
        for (long long exponent = 2; exponent <= n; exponent++) {
            long long ans = calculate(base, exponent, memo);
            if (ans <= n) {
                arr.insert(ans);
            } else {
                break;
            }
        }
    }

    cout << n - arr.size() << endl;
    return EXIT_SUCCESS;
}
