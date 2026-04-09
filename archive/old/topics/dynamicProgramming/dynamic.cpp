#include <bits/stdc++.h>
using namespace std;

long long fib(const long long n, vector<long long> &memo) {
    // returns the nth fibonacci number
    if (memo[n]) {
        return memo[n];
    }

    const long long ans = fib(n - 1, memo) + fib(n - 2, memo);
    memo[n] = ans;
    return ans;
}

int main() {
    long long n;
    cin >> n;

    // this is a recursion with memoization (top-down)
    vector<long long> memo(n + 1, 0); // 1 based indexing
    // all fib(n) > 0  for all n >= 1; so, a zero value of memo[n] indicates we've encountered it the first time
    // save the base cases
    memo[1] = 1;
    memo[2] = 1;
    cout << fib(n, memo) << endl;

    // this is dynamic programming with tabulation (bottom-up)
    vector<long long> dp(n + 1, 0); // 1-based indexing
    dp[1] = dp[2] = 1; // base cases
    for (long long index = 3; index <= n; index++) {
        dp[index] = dp[index - 1] + dp[index - 2]; // bottom-up approach; going from base case to the top case
    }
    cout << dp[n] << endl;

    // this is the same solution as tabulation but with space optimization
    if (n == 1 || n == 2) {
        cout << 1 << endl;
        return EXIT_SUCCESS;
    }

    long long prev = 1;
    long long prev_prev = 1;
    for (long long index = 3; index <= n; index++) {
        const long long curr = prev_prev + prev;
        prev_prev = prev;
        prev = curr;
    }
    cout << prev << endl;
    return EXIT_SUCCESS;
}
