#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string encrypted_password;
    std::cin >> encrypted_password;

    // Create a map to store the binary code to digit mapping.
    // The key is the 10-character binary string, and the value is the character digit ('0' through '9').
    std::map<std::string, char> binary_to_digit_map;

    // Read the 10 binary codes for digits 0-9.
    // The problem guarantees they are provided in order (0, 1, ..., 9).
    for (int i = 0; i < 10; ++i) {
        std::string binary_code;
        std::cin >> binary_code;
        binary_to_digit_map[binary_code] = (char)('0' + i);
    }

    // Restore the 8-digit password.
    // The encrypted_password is 80 characters long, composed of 8 chunks of 10 characters each.
    std::string result_password = "";
    for (int i = 0; i < 8; ++i) {
        // Extract a 10-character chunk from the encrypted password.
        // The first chunk starts at index 0, second at 10, third at 20, etc.
        std::string current_chunk = encrypted_password.substr(i * 10, 10);
        
        // Look up the extracted chunk in the map to find its corresponding digit
        // and append it to the result_password.
        result_password += binary_to_digit_map[current_chunk];
    }

    // Print the restored password to standard output.
    std::cout << result_password << std::endl;

    return 0;
}