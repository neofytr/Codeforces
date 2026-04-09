#include <bits/stdc++.h>

// Function to check if a character is valid for username, hostname words, or resource
bool isValidPartChar(char c) {
    return std::isalnum(c) || c == '_';
}

// Function to validate a username or resource part
bool validateUserOrResource(const std::string& part) {
    if (part.empty() || part.length() > 16) {
        return false;
    }
    for (char c : part) {
        if (!isValidPartChar(c)) {
            return false;
        }
    }
    return true;
}

// Function to validate hostname part
bool validateHostname(const std::string& hostname_str) {
    if (hostname_str.empty() || hostname_str.length() > 32) {
        return false;
    }

    // Hostname cannot start or end with a period
    if (hostname_str[0] == '.' || hostname_str.back() == '.') {
        return false;
    }

    int current_word_len = 0;
    for (char c : hostname_str) {
        if (c == '.') {
            // A word must have at least one character before a period (no consecutive dots like "a..b")
            if (current_word_len == 0) {
                return false;
            }
            current_word_len = 0;
        } else {
            if (!isValidPartChar(c)) {
                return false;
            }
            current_word_len++;
            // Each word in hostname must be between 1 and 16 characters
            if (current_word_len > 16) {
                return false;
            }
        }
    }
    // After the loop, the last word's length must be positive
    // This implicitly covers cases like "a." that might not be caught by hostname_str.back() == '.'
    // if a complex chain of logic was followed, but the explicit check above is more robust.
    if (current_word_len == 0) {
        return false;
    }
    
    return true;
}

void solve() {
    std::string s;
    std::cin >> s;

    // Check total length of the input string
    if (s.empty() || s.length() > 100) {
        std::cout << "NO\n";
        return;
    }

    // Find the position of '@'
    size_t at_pos = s.find('@');
    if (at_pos == std::string::npos) { // No '@' symbol found
        std::cout << "NO\n";
        return;
    }
    // Check for multiple '@' symbols
    if (s.find('@', at_pos + 1) != std::string::npos) {
        std::cout << "NO\n";
        return;
    }
    // Check for empty username or empty hostname part (e.g., "@host", "user@")
    if (at_pos == 0 || at_pos == s.length() - 1) {
        std::cout << "NO\n";
        return;
    }

    // Extract and validate username
    std::string username_str = s.substr(0, at_pos);
    if (!validateUserOrResource(username_str)) {
        std::cout << "NO\n";
        return;
    }

    // Extract the part after '@' which contains hostname and optional resource
    std::string hostname_and_resource_part = s.substr(at_pos + 1);

    // Find the position of '/' for the optional resource part
    size_t slash_pos = hostname_and_resource_part.find('/');

    std::string hostname_str;
    std::string resource_str; 

    if (slash_pos == std::string::npos) { // No resource part
        hostname_str = hostname_and_resource_part;
    } else { // Resource part is present
        hostname_str = hostname_and_resource_part.substr(0, slash_pos);
        resource_str = hostname_and_resource_part.substr(slash_pos + 1);
        
        // Hostname part cannot be empty before the slash (e.g., "user@/resource")
        if (hostname_str.empty()) {
            std::cout << "NO\n";
            return;
        }

        // Resource part cannot be empty after the slash (e.g., "user@host/")
        if (resource_str.empty()) {
            std::cout << "NO\n";
            return;
        }

        // Validate the resource part
        if (!validateUserOrResource(resource_str)) {
            std::cout << "NO\n";
            return;
        }
    }
    
    // Validate the hostname part
    if (!validateHostname(hostname_str)) {
        std::cout << "NO\n";
        return;
    }

    // If all checks pass
    std::cout << "YES\n";
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}