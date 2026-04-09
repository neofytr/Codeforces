#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string s;
    std::cin >> s;

    int n = s.length();
    int max_len = 0; // Initialize the maximum length found to 0

    // Iterate over all possible starting positions of a substring
    for (int i = 0; i < n; ++i) {
        // Iterate over all possible ending positions of a substring
        // 'j' goes from 'i' to 'n-1' to include substrings of length 1 up to n-i
        for (int j = i; j < n; ++j) {
            // Extract the current substring from s starting at index i with length (j - i + 1)
            std::string current_sub = s.substr(i, j - i + 1);
            int sub_len = current_sub.length();

            // Find the first occurrence of current_sub in the original string s
            // The search starts from index 0
            size_t pos1 = s.find(current_sub, 0);

            // If the first occurrence is found (which it should be, as we extracted it from s)
            // then try to find a second occurrence.
            if (pos1 != std::string::npos) {
                // Find a second occurrence of current_sub.
                // The search starts from 'pos1 + 1' to ensure it's a distinct occurrence.
                // This correctly handles overlapping occurrences as described in the problem.
                size_t pos2 = s.find(current_sub, pos1 + 1);
                
                // If a second occurrence is found, it means current_sub appears at least twice.
                // Update max_len if the current substring is longer than any previously found.
                if (pos2 != std::string::npos) {
                    max_len = std::max(max_len, sub_len);
                }
            }
        }
    }

    // Output the maximum length found
    std::cout << max_len << std::endl;

    return 0;
}