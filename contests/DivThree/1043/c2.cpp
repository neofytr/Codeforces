#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_POW = 25;
vector<long long> p3(MAX_POW + 1);
vector<long long> cost(MAX_POW);

void precompute() {
    p3[0] = 1;
    for (int i = 1; i <= MAX_POW; ++i) {
        p3[i] = p3[i-1] * 3;
    }
    cost[0] = 3;
    for (int i = 1; i < MAX_POW; ++i) {
        cost[i] = p3[i+1] + (long long)i * p3[i-1];
    }
}

void solve() {
    long long n, k;
    cin >> n >> k;

    vector<long long> c(MAX_POW, 0);
    long long temp_n = n;
    int max_i = 0;
    for (int i = 0; i < MAX_POW && temp_n > 0; ++i) {
        c[i] = temp_n % 3;
        temp_n /= 3;
        if (c[i] > 0) {
            max_i = i;
        }
    }

    long long d_min = 0;
    for (int i = 0; i <= max_i; ++i) {
        d_min += c[i];
    }

    if (k < d_min) {
        cout << -1 << endl;
        return;
    }

    long long current_cost = 0;
    for (int i = 0; i <= max_i; ++i) {
        current_cost += c[i] * cost[i];
    }

    long long k_rem = k - d_min;

    for (int i = MAX_POW - 2; i >= 0; --i) {
        if (k_rem < 2) {
            break;
        }
        if (c[i + 1] > 0) {
            long long num_breakdowns = min(c[i + 1], k_rem / 2);
            if (num_breakdowns > 0) {
                current_cost -= num_breakdowns * p3[i];
                k_rem -= 2 * num_breakdowns;
                c[i] += 3 * num_breakdowns;
                c[i + 1] -= num_breakdowns;
            }
        }
    }

    cout << current_cost << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}