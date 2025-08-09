#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define int long long

using namespace std;

double solve(int i, int j, const vector<int> &t_indices, vector<vector<double>> &memo) {
    if (i > j || (j - i + 1) < 3) {
        return 0.0;
    }

    if (memo[i][j] != -1.0) {
        return memo[i][j];
    }

    double numerator = j - i - 1;
    double denominator = t_indices[j] - t_indices[i] - 1;
    double current_rate = numerator / denominator;

    double res_sub1 = solve(i + 1, j, t_indices, memo);

    double res_sub2 = solve(i, j - 1, t_indices, memo);

    double max_val = max({current_rate, res_sub1, res_sub2});
    memo[i][j] = max_val;
    return memo[i][j];
}

int32_t main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> str;

    vector<int> t_indices;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == 't') {
            t_indices.push_back(i);
        }
    }

    int k = t_indices.size();

    if (k < 3) {
        cout << fixed << setprecision(24) << 0.0 << endl;
        return EXIT_SUCCESS;
    }

    vector<vector<double>> memo(k, vector<double>(k, -1.0));
    double result = solve(0, k - 1, t_indices, memo);

    cout << fixed << setprecision(24) << result << endl;

    return EXIT_SUCCESS;
}