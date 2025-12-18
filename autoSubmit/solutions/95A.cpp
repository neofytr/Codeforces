#include <iostream>
#include <vector>
#include <string>
#include <cctype> // For std::tolower, std::toupper, std::islower, std::isupper
#include <bits/stdc++.h> // Required for problem statement

// Function to convert a string to lowercase
std::string to_lower_string(const std::string& s) {
    std::string res = s;
    for (char &c : res) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return res;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<std::string> forbidden_raw(n);
    std::vector<std::string> forbidden_lower(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> forbidden_raw[i];
        forbidden_lower[i] = to_lower_string(forbidden_raw[i]);
    }

    std::string w_raw;
    std::cin >> w_raw;
    std::string w_lower = to_lower_string(w_raw);

    char lucky_letter_lower;
    std::cin >> lucky_letter_lower;
    char lucky_letter_upper = std::toupper(static_cast<unsigned char>(lucky_letter_lower));

    std::vector<bool> is_covered(w_raw.length(), false);

    // Find all occurrences of forbidden substrings
    for (int i = 0; i < n; ++i) {
        const std::string& current_forbidden_lower = forbidden_lower[i];
        int forbidden_len = current_forbidden_lower.length();

        // Constraint: strings are non-empty, so forbidden_len > 0
        // if (forbidden_len == 0) continue; 

        for (int j = 0; j <= (int)w_raw.length() - forbidden_len; ++j) {
            std::string w_sub_lower = w_lower.substr(j, forbidden_len);
            if (w_sub_lower == current_forbidden_lower) {
                // Mark all characters in this occurrence as covered
                for (int k = 0; k < forbidden_len; ++k) {
                    is_covered[j + k] = true;
                }
            }
        }
    }

    // Construct the result string
    std::string result = w_raw;
    for (int i = 0; i < (int)w_raw.length(); ++i) {
        if (is_covered[i]) {
            char original_char = result[i];
            char replacement_char;

            // Rule interpretation based on both examples:
            // 1. If the character is covered AND it's NOT the lucky letter (case-insensitive):
            //    Replace it with the lucky letter, preserving its original case.
            //    (This maximizes the lucky letter count).
            // 2. If the character is covered AND it IS the lucky letter (case-insensitive):
            //    We are forced to replace it with "any OTHER one". To satisfy "maximize lucky letter count"
            //    (as much as possible, given the constraint) and then "lexicographically smallest",
            //    we pick the lexicographically smallest character that is DIFFERENT from the original char,
            //    and preserves its case. This would be 'a'/'A', unless the lucky letter itself is 'a'/'A',
            //    in which case we pick 'b'/'B'.
            
            if (std::tolower(static_cast<unsigned char>(original_char)) == lucky_letter_lower) {
                // Original character is already the lucky one. Must replace with a DIFFERENT one.
                if (std::islower(static_cast<unsigned char>(original_char))) {
                    if (lucky_letter_lower == 'a') {
                        replacement_char = 'b';
                    } else {
                        replacement_char = 'a';
                    }
                } else { // original_char is uppercase
                    if (lucky_letter_upper == 'A') {
                        replacement_char = 'B';
                    } else {
                        replacement_char = 'A';
                    }
                }
            } else {
                // Original character is NOT the lucky one. Change to lucky letter.
                if (std::islower(static_cast<unsigned char>(original_char))) {
                    replacement_char = lucky_letter_lower;
                } else {
                    replacement_char = lucky_letter_upper;
                }
            }
            result[i] = replacement_char;
        }
    }

    std::cout << result << std::endl;

    return 0;
}