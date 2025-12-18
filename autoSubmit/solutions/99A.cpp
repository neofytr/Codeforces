#include <bits/stdc++.h>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    std::string s;
    std::cin >> s;

    // Find the position of the dot
    size_t dot_pos = s.find('.');

    // Extract the integer part string
    // The problem guarantees a non-empty integer part before the dot.
    std::string integer_part_str = s.substr(0, dot_pos);

    // Get the last digit of the integer part
    char last_digit_of_integer_part = integer_part_str.back();

    // Rule: If the number's integer part ends with digit 9
    if (last_digit_of_integer_part == '9') {
        std::cout << "GOTO Vasilisa.\n";
    } else {
        // Get the first digit of the fractional part
        // The problem guarantees a non-empty fractional part after the dot.
        char first_fractional_digit_char = s[dot_pos + 1];
        int first_fractional_digit_int = first_fractional_digit_char - '0'; // Convert char to int

        // Rule 1: If fractional part is strictly less than 0.5
        if (first_fractional_digit_int < 5) {
            std::cout << integer_part_str << "\n";
        }
        // Rule 2: If fractional part is not less than 0.5 (i.e., >= 0.5)
        else {
            // Add 1 to the last digit of the number's integer part.
            // Since we've already checked that the last digit is not '9',
            // simply incrementing the character value works directly,
            // e.g., '0' becomes '1', '1' becomes '2', ..., '8' becomes '9'.
            // This operation will not cause a carry-over beyond the last digit
            // because the last digit is guaranteed not to be '9'.
            integer_part_str.back()++;
            std::cout << integer_part_str << "\n";
        }
    }

    return 0;
}