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

    return 0;
}