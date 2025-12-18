#include <bits/stdc++.h>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<int> sticks(4);
    for (int i = 0; i < 4; ++i) {
        std::cin >> sticks[i];
    }

    // Sort the stick lengths to simplify triangle inequality checks.
    // After sorting, sticks[0] <= sticks[1] <= sticks[2] <= sticks[3].
    std::sort(sticks.begin(), sticks.end());

    // max_formable_type will store the highest type of triangle we can form:
    // 0: Impossible
    // 1: Degenerate triangle (SEGMENT)
    // 2: Non-degenerate triangle (TRIANGLE)
    int max_formable_type = 0;

    // We need to check all C(4,3) = 4 combinations of three sticks.
    // The combinations are:
    // 1. (sticks[0], sticks[1], sticks[2])
    // 2. (sticks[0], sticks[1], sticks[3])
    // 3. (sticks[0], sticks[2], sticks[3])
    // 4. (sticks[1], sticks[2], sticks[3])
    // For each combination (a, b, c) where a <= b <= c, the conditions are:
    // - Non-degenerate triangle: a + b > c
    // - Degenerate triangle: a + b == c
    // - No triangle: a + b < c (already implied by the problem structure if neither of the above)

    // First, check if a non-degenerate triangle can be formed by any combination.
    // If we find one, we immediately know the answer is "TRIANGLE" due to priority.
    
    // Combination 1: sticks[0], sticks[1], sticks[2]
    if (sticks[0] + sticks[1] > sticks[2]) {
        max_formable_type = 2;
    }
    // Combination 2: sticks[0], sticks[1], sticks[3]
    if (sticks[0] + sticks[1] > sticks[3]) {
        max_formable_type = 2;
    }
    // Combination 3: sticks[0], sticks[2], sticks[3]
    if (sticks[0] + sticks[2] > sticks[3]) {
        max_formable_type = 2;
    }
    // Combination 4: sticks[1], sticks[2], sticks[3]
    if (sticks[1] + sticks[2] > sticks[3]) {
        max_formable_type = 2;
    }

    // If max_formable_type is 2, a non-degenerate triangle was found.
    if (max_formable_type == 2) {
        std::cout << "TRIANGLE\n";
        return 0;
    }

    // If no non-degenerate triangle was found, check if a degenerate triangle (segment) can be formed.
    // We update max_formable_type only if it's currently 0 (impossible) and we find a degenerate triangle.
    
    // Combination 1: sticks[0], sticks[1], sticks[2]
    if (sticks[0] + sticks[1] == sticks[2]) {
        max_formable_type = std::max(max_formable_type, 1);
    }
    // Combination 2: sticks[0], sticks[1], sticks[3]
    if (sticks[0] + sticks[1] == sticks[3]) {
        max_formable_type = std::max(max_formable_type, 1);
    }
    // Combination 3: sticks[0], sticks[2], sticks[3]
    if (sticks[0] + sticks[2] == sticks[3]) {
        max_formable_type = std::max(max_formable_type, 1);
    }
    // Combination 4: sticks[1], sticks[2], sticks[3]
    if (sticks[1] + sticks[2] == sticks[3]) {
        max_formable_type = std::max(max_formable_type, 1);
    }

    // Based on the final max_formable_type, output the result.
    if (max_formable_type == 1) {
        std::cout << "SEGMENT\n";
    } else { // max_formable_type is still 0, meaning no type of triangle could be formed.
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}