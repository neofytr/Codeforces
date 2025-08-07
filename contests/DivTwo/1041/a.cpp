#include <iostream>
#include <numeric>
#include <vector>

// Function to handle a single test case
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int target_val = -1; // To store the first non -1 positive value we find
    bool possible = true;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Iterate through the array to check the conditions
    for (int x : a) {
        // Condition 1: A "good" array cannot contain 0.
        if (x == 0) {
            possible = false;
            break;
        }

        // Condition 2: All existing numbers must be the same positive integer.
        if (x != -1) {
            if (target_val == -1) {
                // This is the first non -1 number we've encountered.
                // Set it as the target value for the whole array.
                target_val = x;
            } else {
                // We already have a target value. This element must match it.
                if (x != target_val) {
                    possible = false;
                    break;
                }
            }
        }
    }

    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve();
    }

    return 0;
}