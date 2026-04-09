#include <bits/stdc++.h>
using namespace std;

/*
 * Where DP?
 * 1. overlapping subproblems
 * 2. minimize/maximize some value
 * 3. finding number of ways
 * 4. covering all cases (DP v/s Greedy)
 * 5. check for possibility
 */

#define int long long

int solveFib(const int x, vector<int> &dp) {
    if (x == 1 || x == 2)
        return dp[x] = 1;
    if (dp[x] != -1)
        return dp[x];
    return dp[x] = solveFib(x - 1, dp) + solveFib(x - 2, dp);
}

void fib() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, -1);
    cout << solveFib(n, dp) << endl;
}

int solveGrid(int r, int c, vector<vector<int>> &g, vector<vector<int>> &dp) {
    int n = (int)g.size();
    int m = (int)g[0].size();

    if (r >= n || c >= m)
        return LLONG_MAX;

    if (dp[r][c] != -1)
        return dp[r][c];

    return g[r][c] + min(solveGrid(r + 1, c, g, dp), solveGrid(r, c + 1, g, dp));
}

void gridTwo() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> g[row][col];

    // dp[r][c] gives the minimum sum of values path from (r, c) to (n - 1, m - 1)
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << solveGrid(0, 0, g, dp) << endl;
}

void grid() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> g[row][col];

    // we can only move down or right from any cell

    // dp[r][c] gives the minimum sum of values path from (0, 0) to (r, c)
    vector<vector<int>> dp(n, vector<int>(m, LLONG_MAX));

    queue<tuple<int, int>> que;
    int dr[] = {0, +1};
    int dc[] = {+1, 0};
    dp[0][0] = g[0][0];
    que.push({0, 0});
    while (!que.empty()) {
        auto [row, col] = que.front();
        que.pop();

        for (int i = 0; i < 2; i++) {
            int drow = row + dr[i];
            int dcol = col + dc[i];
            if (drow >= 0 && dcol >= 0 && drow < n && dcol < m) {
                if (dp[drow][dcol] > dp[row][col] + g[drow][dcol]) {
                    dp[drow][dcol] = dp[row][col] + g[drow][dcol];
                    que.push({drow, dcol});
                }
            }
        }
    }

    cout << dp[n - 1][m - 1] << endl;
}

int solveSub(int x, vector<int> &arr, vector<int> &dp) {
    int n = (int)arr.size();
    if (x >= n)
        return 0;

    if (dp[x] != -1)
        return dp[x];

    // we can either pick this element, or we don't
    return dp[x] = max(solveSub(x + 1, arr, dp), arr[x] + solveSub(x + 2, arr, dp));
}

void subseqThree() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to find a subsequence of arr such that no two elements in the subsequence
    // are adjacent in the array and the sum of the elements in the subsequence is maximized

    // dp[r][0] is the maximum subsequence sum for such a subsequence in the subarray [0, r]
    // such that we don't pick the element r in the subsequence

    // dp[r][1] is the maximum subsequence sum for a subsequence in the subarray [0, r] such that
    // we pick the element r in the subsequence
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = arr[0];
    dp[1][0] = max(arr[0], 0LL);
    dp[1][1] = arr[1];
    for (int r = 2; r < n; r++) {
        dp[r][0] = max(dp[r - 1][0], dp[r - 1][1]);
        dp[r][1] = arr[r] + max(dp[r - 2][0], dp[r - 2][1]); // or arr[r] + dp[r - 1][0]
    }
    cout << max(dp[n - 1][0], dp[n - 1][1]) << endl;
}

void subseqTwo() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to find a subsequence of arr such that no two elements in the subsequence
    // are adjacent in the array and the sum of the elements in the subsequence is maximized

    // dp[r] is the maximum sum for such a subsequence in the subarray [0, r]
    vector<int> dp(n, -1);

    dp[0] = arr[0];
    dp[1] = max(arr[0], arr[1]);
    for (int r = 2; r < n; r++) {
        // either we can pick the current element or we don't pick the current element
        // in the maximum sum subsequence in the subarray [0, r - 1]
        dp[r] = max(dp[r - 1], dp[r - 2] + arr[r]);
    }
    cout << dp[n - 1] << endl;
}

void subseq() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to find a subsequence of arr such that no two elements in the subsequence
    // are adjacent in the array and the sum of the elements in the subsequence is maximized

    // dp[r] is the maximum subsequence sum for such a subsequence in the array segment [r, n - 1]
    vector<int> dp(n, -1);
    cout << solveSub(0, arr, dp) << endl;
}

int32_t main() {
    /*
     * States and Transitions
     *
     * State -> A subproblem that we want to solve. The subproblem may be complex or easy to solve
     * but the final aim is to solve the final problem which may be defined by a relation between the smaller
     * subproblems. A state is represented with some parameters.
     *
     * Transition -> Calculating the answer for a state (subproblem) by using the answers of
     * other smaller states (subproblems). This is represented as a relation between states.
     *
     */

    // a very important result to calculate time complexity in some cases ->
    /*
     *  n / 1 + n / 2 + n / 3 + n / 4 .... <= nlog(n)
     */

    /*
     * Time Complexity ->
     * Estimate -> Number of States * Transition time for each state
     * Exact -> Total transition time for all states
     *
     * Space Complexity ->
     * Number of states * space required for each state (for an iterative solution)
     */

    /*
     * Recursive v/s Iterative DP
     *
     * Recursive ->
     * 1. Slower (runtime)
     * 2. No need to care about the flow
     * 3. Does not evaluate unnecessary states
     * 4. Cannot apply many optimizations
     *
     * Iterative ->
     * 1. Faster (runtime)
     * 2. Important to calculate states in a way that current state can be derived from
     * previously calculated states
     * 3. All states are evaluated
     * 4. Can apply optimizations
     */

    /*
     * General Technique to solve any DP problem
     * 1. State
     * Clearly define the subproblem.
     * Clearly understand when you are saying dp[i][j][k], what does it
     * represent exactly
     *
     * 2.
     * Transition
     * Now we define a relation between states.
     * Assume that states on the right side of the equation have been
     * calculated.
     * Don't worry about them.
     *
     * 3. Base Case
     * For what states does your transition fail or goes into some absurd value?
     * Call them the base cases and handle them separately beforehand.
     *
     * 4. Final subproblem
     * What is the problem demanding you to find?
     * The final subproblem depends on what the problem statement is and how are we defining the states.
     */

    /*
     * Break the bigger problem into chunks of smaller subproblems that are easier to think about and solve. Call
     * each of the subproblems a state and use some parameters to uniquely identify each state.
     * Now, try to think of a relation that solves a subproblem in terms of smaller subproblems.
     * Identify base cases and solve the final problem.
     */

    /*
     * for r >= 1, if dp[r] is dependent upon states in the prefix [0, r-1] and we have dp[0] as a base case,
     * run the iterative loop from 1 to n
     *
     * for r <= n - 1, if dp[r] is dependent upon states from suffix [r + 1, n] and we have
     * dp[n] as the base case, run the iterative loop from n - 1 to 0
     */

    /*
     * DP v/s Greedy
     * We should always prove a greedy solution will work before going forward with it. This we won't be
     * required to do when we are doing a DP solution.
     */

    /*
     * Space Optimization
     * 1. What other state does our current state depend on?
     * 2. Do we need answers to all subproblems at all times?
     * 3. Well, let's store only relevant states then!
     * 4. But wait, does this always work?
     *    - what if the final subproblem requires all the states?
     *    - what if we need to backtrack?
     */

    /*
     * On codeforces in C++, we can do an order of 10^8 operations in a second before we get a TLE, BUT
     * , we cannot utilize memory on the order of 10^8 bytes
     * The largest memory we can utilize is on the order of 10^7 bytes
     *
     * So, if we have O(nm) time complexity where nm <= 10^8, we cannot have O(nm) space complexity
     *
     * This is why we require space optimization in DP, and that is why iterative DP is the better option for
     * harder problems
     */

    /*
     * State Optimization
     * 1. Ask yourself do you need all the parameters in the dp state?
     * 2. If you have dp[a][b][c] and you can find c = f(a, b), do you need to store c as a parameter
     * or can you just compute it on spot?
     * 3. If you can compute a parameter in dp state from other parameters, no need to store that parameter
     * in the state
     * 4. This reduces both time and space complexity
     * 5. In general, if we have dp[a][b][c] and we have some relation between a, b and c, we should
     * remove that parameter which has the highest upper bound.
     * 6. Which parameter you should remove? the one with the highest upper bound
     */

    /*
     * Transition Optimization
     * 1. Observe the transition equation
     * 2. Can you do some pre-computation to evaluate the equation faster?
     * 3. Using clever observations
     * 4. Using range query data structures
     */

    /*

        Clever Transition Optimizations

        1. Cumulative sums often turn into telescoping patterns
        or can be rewritten using prefix sums to avoid repeated work.

        dp[r] = dp[r - 1] + dp[r - 2] + ... + dp[0]
        This transition can be optimized as ->
        dp[r] = dp[r - 1] + dp[r - 1] = 2 * dp[r - 1]

       2. Whenever a DP transition involves a "range minimum / maximum"
       over consecutive indices, it can usually be accelerated with RMQ data
       structures or sliding window tricks.

        dp[r] = min(dp[r - 1], dp[r - 2], ...., dp[r - arr[r]])
        This transition can be optimized using a range query data structure that can give
        range minimum in log(n)

     */

    return 0;
}