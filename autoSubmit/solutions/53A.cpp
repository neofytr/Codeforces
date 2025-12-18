#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s; // Read the inputted part s

    int n;
    std::cin >> n; // Read the number of visited pages

    std::string min_matching_page = ""; // Stores the lexicographically smallest page that starts with s
    bool found_match = false; // Flag to indicate if any page matching s as a prefix has been found

    // Iterate through n visited pages
    for (int i = 0; i < n; ++i) {
        std::string current_page;
        std::cin >> current_page; // Read the current visited page

        // Check if current_page starts with s
        // 1. current_page must be at least as long as s
        // 2. The substring of current_page from index 0 with length s.length() must be equal to s
        if (current_page.length() >= s.length() && current_page.compare(0, s.length(), s) == 0) {
            if (!found_match) {
                // If this is the first page found that matches the prefix s
                min_matching_page = current_page;
                found_match = true;
            } else {
                // If we've already found a matching page, compare current_page with the stored minimum
                // If current_page is lexicographically smaller, update min_matching_page
                if (current_page < min_matching_page) {
                    min_matching_page = current_page;
                }
            }
        }
    }

    // Output the result
    if (!found_match) {
        // If no page was found that starts with s, print s itself
        std::cout << s << std::endl;
    } else {
        // Otherwise, print the lexicographically smallest matching page found
        std::cout << min_matching_page << std::endl;
    }

    return 0;
}