#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// For fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    long long n, m, k;
    std::cin >> n >> m >> k;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (n % 2 == 0) {
        // If n is even, the sum of all elements must remain constant
        // to satisfy A[i] + A[i+1] = S_i for all i.
        // The condition A_new[i] + A_new[i+1] = A_old[i] + A_old[i+1] for all i
        // implies that A_new[i] = A_old[i] + (-1)^(i-1) * delta_1 for some constant delta_1.
        // The total sum of diamonds in the cells becomes:
        // sum(A_new) = sum(A_old) + delta_1 * sum((-1)^(i-1) for i=1 to n).
        // If n is even, sum((-1)^(i-1)) from i=1 to n is (1 - 1 + 1 - 1 ... + 1 - 1) = 0.
        // Therefore, sum(A_new) = sum(A_old).
        // This means no diamonds can be stolen (removed from the system) while maintaining the security condition,
        // as stealing reduces the total sum of diamonds in the cells.
        std::cout << 0 << std::endl;
    } else {
        // If n is odd:
        // The state change from A_old to A_new that maintains the sums S_i is:
        // A_new[i] = A_old[i] - X for odd i (1-indexed)
        // A_new[i] = A_old[i] + X for even i (1-indexed)
        // where X is the amount of diamonds we aim to steal.
        // The total sum of diamonds in the cells becomes:
        // sum(A_new) = sum(A_old) + delta_1 * sum((-1)^(i-1) for i=1 to n).
        // If n is odd, sum((-1)^(i-1)) from i=1 to n is (1 - 1 + 1 - 1 ... + 1) = 1.
        // To steal X diamonds, we need sum(A_old) - sum(A_new) = X.
        // This implies delta_1 = -X.
        // So A_new[i] = A_old[i] + (-1)^(i-1) * (-X) = A_old[i] - X * (-1)^(i-1).
        // For odd i (1-indexed), i-1 is even, so (-1)^(i-1) = 1. A_new[i] = A_old[i] - X.
        // For even i (1-indexed), i-1 is odd, so (-1)^(i-1) = -1. A_new[i] = A_old[i] + X.

        // 1. Constraint on X from non-negativity of diamonds:
        // All A_new[i] must be non-negative.
        // For odd i: A_old[i] - X >= 0  =>  X <= A_old[i].
        // This must hold for all odd i. So, X <= min(A_old[i] for all odd i).
        // For even i: A_old[i] + X >= 0. This is always true since A_old[i] >= 0 and X >= 0.
        long long min_val_odd_indices = -1; // Using -1 as a sentinel for first element
        for (int i = 0; i < n; i += 2) { // Loop through 0-indexed a[0], a[2], ... (which correspond to 1-indexed odd positions)
            if (min_val_odd_indices == -1 || a[i] < min_val_odd_indices) {
                min_val_odd_indices = a[i];
            }
        }
        
        // 2. Constraint on X from operations limit:
        // To achieve a steal of X diamonds and the required state change:
        // - Each of the (n+1)/2 odd cells must decrease by X diamonds.
        // - Each of the (n-1)/2 even cells must increase by X diamonds.
        //
        // The total diamonds to be supplied to even cells is X * ((n-1)/2).
        // These can be taken from odd cells. Moving X diamonds from one cell to another costs X operations.
        // So, X * ((n-1)/2) operations are used for cell-to-cell transfers (odd to even cells).
        //
        // The total diamonds removed from odd cells is X * ((n+1)/2).
        // After supplying X * ((n-1)/2) diamonds to even cells, the remaining diamonds
        // to be removed from odd cells are:
        // X * ((n+1)/2) - X * ((n-1)/2) = X * ( (n+1 - (n-1))/2 ) = X * (2/2) = X.
        // These X diamonds are moved to Joe's pocket. This costs X operations (cell-to-pocket).
        //
        // Total operations required = (X * (n-1)/2) + X = X * ((n-1)/2 + 1) = X * ((n-1+2)/2) = X * (n+1)/2.
        // Joe has `k` minutes, with `m` operations per minute, so total available operations = `m * k`.
        // Thus, X * (n+1)/2 <= m * k.
        // X <= (m * k) / ((n+1)/2)
        // X <= (2 * m * k) / (n+1)
        
        // Note: m, k can be up to 10^9, so m*k can be up to 10^18. Use long long for calculations.
        long long max_steal_by_ops = (2LL * m * k) / (n + 1);

        // The maximum amount Joe can steal is limited by both the non-negativity constraint
        // and the available operations.
        long long max_steal = std::min(min_val_odd_indices, max_steal_by_ops);
        std::cout << max_steal << std::endl;
    }

    return 0;
}