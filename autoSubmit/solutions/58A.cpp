#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;

    std::string target = "hello";
    int target_idx = 0; // Pointer for the target string "hello"

    // Iterate through the input string s
    for (char c : s) {
        // If we still have characters to find in "hello"
        // and the current character from s matches the character we are looking for in "hello"
        if (target_idx < target.length() && c == target[target_idx]) {
            target_idx++; // Move to the next character in "hello"
        }
    }

    // After iterating through s, check if we successfully found all characters of "hello"
    if (target_idx == target.length()) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}