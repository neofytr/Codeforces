#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    std::vector<int> one_indices;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            one_indices.push_back(i);
        }
    }

    // The problem guarantees that the given record sequence contains at least three 1s.
    // This means one_indices will have at least 3 elements.
    // Therefore, there will always be at least two intervals to compare.
    // The first interval is between the first two '1's.
    int expected_interval = one_indices[1] - one_indices[0];
    bool all_intervals_equal = true;

    // Check all subsequent intervals against the first one.
    // Start from the third '1' (index 2 in one_indices)
    // and compare the interval between it and the preceding '1'.
    for (int j = 2; j < one_indices.size(); ++j) {
        int current_interval = one_indices[j] - one_indices[j - 1];
        if (current_interval != expected_interval) {
            all_intervals_equal = false;
            break; // Found an unequal interval, no need to check further.
        }
    }

    if (all_intervals_equal) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Fast I/O setup
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}